#include "Config.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#include "Logging.h"

Config::Config(string name, string parentDebugInfo) {
	m_sDebugInfo = parentDebugInfo + ", " + name;
}

Config::Config(string configFile) {
	m_sDebugInfo = configFile;
	m_sConfigFilePath = configFile;
	m_lsGroupStack.push_front(this);
}

bool Config::ReadConfig(){
	FILE* in = fopen(m_sConfigFilePath.c_str(), "r");
	if (!in) {
		cerr << "Cannot open configuration file '" << m_sConfigFilePath << "'" << endl;
		exit(2);
	}

	char buff[1024];
	while (fgets(buff, 1024, in)) {

		string line=buff;
		if ( (line.length() > 2) && (line[0] != '#') && (line.find(')') == string::npos) ) {
			string name;
			string value;
			split(line, name, value, '=');

			if (value == "(") {
				std::string sLogContent = "   config: new group '" + name + "'";
				Log(LOG_DEBUG, sLogContent);
				Config* newGroup = new Config(name, m_sDebugInfo);
				m_lsGroupStack.front()->m_mapGroups[name] = newGroup;
				m_lsGroupStack.push_front(newGroup);
			} else {
				for (list<Config*>::reverse_iterator i = m_lsGroupStack.rbegin(); i != m_lsGroupStack.rend(); ++i) {
					(*i)->symbolExpand(value);
				}
				envSymbolExpand(value);
				std::string sLogContent = "   config: name = '" + name + "', value = '" + value + "'";
				Log(LOG_DEBUG, sLogContent);
				m_lsGroupStack.front()->add(name, value);
			}
		}
		if ( (line.length() > 0) && (line[0] != '#') && (line.find(')') != string::npos) ) {
			std::string sLogContent = "   end of group";
			Log(LOG_DEBUG, sLogContent);
			m_lsGroupStack.pop_front();
		}
	}

	fclose(in);
	return true;
}
Config::~Config() {
	for (map<string, Config*>::iterator i = m_mapGroups.begin(); i != m_mapGroups.end(); ++i) {
		delete i->second;
	}
}

void Config::add(string name, string value) {
	m_mapSymbols[name] = value;
}

void Config::InitValue(string name, string value) {
	m_mapSymbols[name] = value;
}

void Config::split(string in, string& left, string& right, char c) {
	size_t pos = in.find_first_of(c);
	if(pos == string::npos) {
		left = in;
		trim(left);
		right = "";
	} else if (pos <= 1) {
		left = "";
		right = in.substr(pos+1, string::npos);
		trim(right);
	} else {
		left = in.substr(0, pos-1);
		trim(left);
		right = in.substr(pos+1, string::npos);
		trim(right);
	}
}

void Config::trim(string& s) {
	while ( (s.length() > 1) && ( (s[0] == ' ') || (s[0] =='\t') ) ) {
		s = s.substr(1, string::npos);
	}
	while ( (s.length() > 1) &&
			( (s[s.length()-1] == ' ') ||
			  (s[s.length()-1] == '\t') || 
			  (s[s.length()-1] == '\n') || 
			  (s[s.length()-1] == '\r') ) ) {
		s = s.substr(0, s.length()-1);
	}
	if ( (s.length() > 1) && (s[0] == '"') ) {
		s = s.substr(1, string::npos);
	}
	if ( (s.length() > 1) && (s[s.length()-1] == '"') ) {
		s = s.substr(0, s.length()-1);
	}
}

void Config::symbolExpand(string& s) {
	symbolExpand(m_mapSymbols, s);
}

void Config::envSymbolExpand(string& s) {
	symbolExpand(m_mapEnvSymbols, s);
}

void Config::symbolExpand(map<string, string>& m_mapSymbols, string& s) {
	bool expanded;
	do {
		expanded = false;
		for (map<string, string>::iterator i = m_mapSymbols.begin(); i != m_mapSymbols.end(); ++i) {
			string search = "%" + i->first + "%";
			string replace = i->second;
			size_t pos = s.find(search);
			if (pos != string::npos) {
				expanded = true;
				s.replace(pos, search.length(), replace);
			}
		}
	} while (expanded);
}

string Config::GetString(string name) {
	map<string, string>::iterator i = m_mapSymbols.find(name);
	if (i == m_mapSymbols.end()) {
		std::string sLogContent = "access of missing property '" + name + "' (" + m_sDebugInfo + ")";
		Log(LOG_ERROR, sLogContent);
		exit(4);
	}
	return i->second;
}

bool Config::GetBool(string name) {
	string val = GetString(name);

	if ( (val == "yes") ||
	     (val == "Yes") ||
	     (val == "YES") ||
		 (val == "true") ||
	     (val == "True") ||
	     (val == "TRUE"))
	{
		return true;
	}

	return false;
}

double Config::GetDouble(string name) {
	string val = GetString(name);

	return atof(val.c_str());
}

int Config::GetInt(string name) {
	string val = GetString(name);

	return atoi(val.c_str());
}