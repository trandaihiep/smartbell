/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Xử lý tác vụ của camera

*Contributors:
   Tran Dai Hiep:	01-Feb-2018: Initial implementation and documentation.
*****************************************/

///****************  INCLUDE ***************///
#include "CameraHandler.h"


///************** FUCNTION **************///
// Description: Contructor
// Parameters: 
//		
// Return: None
CameraHandler::CameraHandler(){
	
}
///************** FUCNTION **************///
// Description: Decontructor
// Parameters: 
//		
// Return: None
CameraHandler::~CameraHandler(){

}

// Description: Chụp hình từ camera
// Parameters: 
//		
// Return: None
void CameraHandler::CaptureImage(const char* pztcFilePath){
    if( !isOpened() ){
        char* strError;
        strError = "Open camera failed:";
        strError += pztcFilePath;
        Log(LOG_DISP_WARNING, strError);
        return 0;
    }
    cv::Mat frame;
    cap >> frame;
    if( frame.empty() ) {
        std::cout << "Empty Frame" <<  std::endl;
        continue;
    }
    std::string tmp = IMG_PATH + str + ".png"; cout << tmp << endl;
    imwrite(tmp, frame, compression_params);
    tmp = PUB_MESSAGE + str + ".png\"}";	cout << tmp << endl;
    m_pComControl->publish(tmp);
    g_pSmartBellData.m_bAlarmFlag = false;
}


