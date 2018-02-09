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
#include "Units/CommunicateControl.h"
#include "util.h"
#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <chrono>
#include <thread>
#include <ctime>
#include "logging.h"

///****************  DEFINE ****************///
#define THRES 0
///**************  NAMESPACE **************///
using namespace cv;
using namespace std;
using namespace std::chrono;
///***************  VARIABLE **************///
extern static SmartBellData* g_pSmartBellData = NULL;   // Application data
extern static Logging g_sLog;          // Write Log

class CommunicateControl *m_pComControl;
///*************** FUCNTION **************///

void InitializeData(); 		// Khởi tạo dữ liệu
void ListenDataProcess(); 	// Xử lý
void ReleaseData();			// Giải phóng bộ nhớ
void ReceiveHandler(std::string sReceiveData); // Xử lý dữ liệu nhận được

#endif  // SMARTBELL_MAIN_H_