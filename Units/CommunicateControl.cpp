/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Lớp CommunicateControl là lớp bao của lớp mosquitto nhằm cung cấp các giao thức gửi và nhận mesage trong IOT

*Contributors:
   Tran Dai Hiep:	01-Feb-2018: Initial implementation and documentation.
*****************************************/

///****************  INCLUDE ***************///
#include <stdio>
#include <cstring>
#include "Units/CommunicateControl.h"
#include <mosquittopp.h>


///************** FUCNTION **************///
// Description: 
// Parameters: 
//		
// Return: None
CommunicateControl::CommunicateControl(const char *id, const char *host, int port) : mosquittopp(id)
{
	
	int keepalive = 60;
	/* Connect immediately. This could also be done by calling
	 * mqtt_tempconv->connect(). */
	connect(host, port, keepalive);
};

CommunicateControl::~CommunicateControl(){

}

// Description: 
// Parameters: 
//		
// Return: None
void CommunicateControl::on_connect(int rc)
{
	printf("MQTT Connected with code %d.\n", rc);
	if(rc == 0)
	{
		/* Only attempt to subscribe on a successful connect. */
		subscribe(NULL, GWTOPIC);
	}
}

// Description: 
// Parameters: 
//		
// Return: None
void CommunicateControl::on_message(const struct mosquitto_message *message)
{
	char buf[BUFSIZE];
	if(!strcmp(message->topic, GWTOPIC)){
		memset(buf, 0, BUFSIZE*sizeof(char));
		/* Copy N-1 bytes to ensure always 0 terminated. */
		memcpy(buf, message->payload, 200*sizeof(char));
		//printf("Buffer: %s\n", buf);
		m_strHandlerFunction(buf);
		//publish(NULL, "temperature/farenheit", strlen(buf), buf);
	}
}

// Description: 
// Parameters: 
//		
// Return: None
void CommunicateControl::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
	//printf("MQTT Subscription succeeded topic: %s", GWTOPIC);
}

// Description: 
// Parameters: 
//		
// Return: None
void CommunicateControl::addHandler(std::function<void(std::string)> callback)
{
	m_strHandlerFunction = callback;
}

// Description: 
// Parameters: 
//		
// Return: None
void CommunicateControl::publish(std::string message){
	char buf[BUFSIZE];
	char *cstr = new char[message.length() + 1];
	strcpy(cstr, message.c_str());
	mosquittopp::publish(NULL, ALARMTOPIC, strlen(cstr), cstr);
}
