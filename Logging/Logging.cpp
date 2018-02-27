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
#include "Logging.h"

extern LogHandler g_sLog;          // Write Log
///************** FUCNTION **************///
// Description: Hiển thị và lưu lại thông tin
// Parameters: 
//		int nLogLevel: Cấp độ ghi thông tin 
//      const char *pztcContent : Nội dung
//      string      sContent    : Nội dung
// Return: None
void Log(int nLogLevel, const char *pztcContent){
    g_sLog.Log(nLogLevel, pztcContent);

}
void Log(int nLogLevel, std::string sContent){
    g_sLog.Log(nLogLevel, sContent);
}
// Description: Thiết lấp mức độ hiển thị thông tin
// Parameters: 
//		int nLogLevel: Cấp độ ghi thông tin 
// Return: None
void SetLogLevel(int nLogLevel){
    g_sLog.SetDispMode(nLogLevel);
}

