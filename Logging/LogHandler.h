/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
LogHandler xuất bản ghi thông tin (log)
*Contributors:
   Tran Dai Hiep:	01-Feb-2018: Initial implementation and documentation.
*****************************************/
#ifndef LOGHANDLER_H_
#define LOGHANDLER_H_
///****************  INCLUDE ***************///
#include <stdio.h>
#include <cstdio>
#include <string>
///****************  DEFINE ****************///
#define LOG_ERROR 	0x01 //0b0000001
#define LOG_WARNING 0x02 //0b0000010
#define LOG_INFO 	0x04 //0b0000100
#define LOG_DEBUG	0x08 //0b0001000

#define LOG_DISP_NONE 		0
#define LOG_DISP_ERROR 		LOG_ERROR
#define LOG_DISP_WARNING 	LOG_ERROR|LOG_WARNING
#define LOG_DISP_INFO 		LOG_ERROR|LOG_WARNING|LOG_INFO
#define LOG_DISP_DEBUG		LOG_ERROR|LOG_WARNING|LOG_INFO|LOG_DEBUG


///**************  NAMESPACE **************///
using namespace std;
/*
 * Class: LogHandler
 *
 *  Lớp LogHandler xuất bản ghi thông tin (log)
 */
class LogHandler{
   private: //// PRIVATE
		///*************** FUCNTION **************///
		const char * GetLogLevelName(int nLogLevel){
			switch (nLogLevel){
				case LOG_ERROR:
					return "ERROR";
				case LOG_WARNING:
					return "WARN";
				case LOG_INFO:
					return "INFO";
				case LOG_DEBUG:
					return "DEBUG";
				default:
					return "INDETERMINE";
			}
		};
		///*************** VARIABLE **************///
		unsigned int m_byDisplayMode; // Mode hiển thị log
   public: //// PUBLIC
		///*************** FUCNTION **************///
		LogHandler();
		~LogHandler();
		// Get - Set
		unsigned int GetDispMode(){ return m_byDisplayMode; };
		void SetDispMode( unsigned int nDispMode) { m_byDisplayMode = nDispMode;};


		// Process
		void Log(unsigned int nLogLevel, const char *pztcContent);
		void Log(unsigned int nLogLevel, std::string sContent);
		///*************** VARIABLE **************///


};
#endif  // LogHandler