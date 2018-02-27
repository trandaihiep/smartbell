/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Xuất bản ghi thông tin (log)
*Contributors:
   Tran Dai Hiep:	01-Feb-2018: Initial implementation and documentation.
*****************************************/
#ifndef LOGGING_H_
#define LOGGING_H_
///****************  INCLUDE ***************///
#include "LogHandler.h"

///****************  DEFINE ****************///
extern LogHandler g_sLog;          // Write Log

///*************** FUCNTION **************///
void Log(int nLogLevel, const char *pztcContent); // Ghi log
void Log(int nLogLevel, std::string sContent); // Ghi log
void SetLogLevel(int nLogLevel);

#endif  // LogHandler