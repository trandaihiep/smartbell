/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Ghi log

*Contributors:
   Tran Dai Hiep:	01-Feb-2018: Initial implementation and documentation.
*****************************************/

///****************  INCLUDE ***************///
#include "LogHandler.h"
#include <iostream>
#include <string>
#include <ctime>

///************** FUCNTION **************///
// Description: 
// Parameters: 
//		
// Return: None
LogHandler::LogHandler()
{
	m_byDisplayMode = LOG_DISP_INFO;
}

LogHandler::~LogHandler(){

}

void LogHandler::Log(unsigned int nLogLevel, const char *pztcContent){
    // current date/time based on current system
    time_t now = time(0);

    // convert now to string form
    std::string sDatetime = ctime(&now);
    sDatetime.replace(sDatetime.end()-1,sDatetime.end(),""); 
    // Hiển thị log
    if ((nLogLevel & m_byDisplayMode ) != 0){
        const char *pztcLogLevel = GetLogLevelName(nLogLevel);
        printf("%s [%s]: %s",sDatetime.c_str(), pztcLogLevel, pztcContent);
        std::cout <<std::endl;
        // std::cout <<sDatetime.c_str()<< pztcLogLevel<< pztcContent<< std::endl;

    }
    // Ghi log ra file: Chưa code!!!
}

void LogHandler::Log(unsigned int nLogLevel, std::string sContent){
    Log(nLogLevel, sContent.c_str());
}