/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

**************  DESCRIPTION **************
// Liệt kê các DEFINE, NAMESPACE, VARIABLE, FUNCTION sử dụng xử lý chính main()
//
Contributors:
   Tran Dai Hiep:	01-Feb-2018: Initial implementation and documentation.
*****************************************/
#ifndef SMARTBELL_MAIN_H_
#define SMARTBELL_MAIN_H_
///****************  INCLUDE ***************///

#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <chrono>
#include <thread>
#include <ctime>


#include "MQTTConnector.h"
#include "SmartBellData.h"
#include "CameraHandler.h"
#include "LogHandler.h"

///****************  DEFINE ****************///
#define THRES 0
///**************  NAMESPACE **************///
using namespace cv;
using namespace std;
using namespace std::chrono;
///***************  VARIABLE **************///
extern SmartBellData*    g_pSmartBellData = NULL;   // Application data
extern bool                     g_bProcessing =  false;    // Cờ báo việc đang xử lý dữ liệu
extern MQTTConnector *          m_pComControl = NULL;
///*************** FUCNTION **************///

void InitializeData(); 		// Khởi tạo dữ liệu
void ProcessDataQueue(); 	// Xử lý
void ReleaseData();			// Giải phóng bộ nhớ
void ReceiveHandler(std::string sReceiveData); // Xử lý dữ liệu nhận được

//void * ProcessBellDataCaptureImage( void *args);
void ProcessBellDataCaptureImage(BellData* pBellDt);
void ProcessDataQueue();
// LOG
void Log(int nLogLevel, const char *pztcContent); // Ghi log
void Log(int nLogLevel, std::string sContent); // Ghi log
void SetLogLevel(int nLogLevel);

#endif  // SMARTBELL_MAIN_H_