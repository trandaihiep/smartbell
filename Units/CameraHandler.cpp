/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Xử lý tác vụ của camera

*Contributors:
   Pham Chi Viet Hung:	08-Feb-2018: Initial implementation and documentation.
*****************************************/

///****************  INCLUDE ***************///
#include "CameraHandler.h"

///************** FUCNTION **************///
// Description: Contructor
// Parameters: 
//		
// Return: None
CameraHandler::CameraHandler(){
	m_pCamData = NULL;

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
// void Camera::CaptureImage(){
//     if( !isOpened() ){
//         char* strError;
//         strError = "Open camera failed:";
//         Log(LOG_DISP_WARNING, strError);
//         return 0;
//     }
//     cv::Mat frame;
//     cap >> frame;
//     if( frame.empty() ) {
//         std::cout << "Empty Frame" <<  std::endl;
//         continue;
//     }
//     std::string tmp = IMG_PATH + str + ".png"; cout << tmp << endl;
//     imwrite(tmp, frame, compression_params);
//     tmp = PUB_MESSAGE + str + ".png\"}";	cout << tmp << endl;
//     m_pComControl->publish(tmp);
//     g_pSmartBellData.m_bAlarmFlag = false;
// }
// Description: Chụp hình từ camera
// Parameters: 
//		
// Return: None
void CameraHandler::SetCamdata(CameraData* pCamData){
    m_pCamData = pCamData;
}


void CameraHandler::SaveImage(){
    cv::imwrite(IMAGE_DIR + m_pCamData->GetCamID() + "/" + m_pCamData->GetPath(),m_pCamData->GetImage());
}
// Description: Chụp hình từ camera
// Parameters: 
//		
// Return: None

CaptureResult CameraHandler::CaptureImage(){
     
	if(!m_pCamData->GetMainURL().empty()){
        cv::VideoCapture cap(m_pCamData->GetMainURL(), cv::VideoCaptureAPIs::CAP_GSTREAMER);
        if( cap.isOpened() )
        {
            cv::Mat frame;
            cap >> frame;
            if( !frame.empty() ) {
                m_pCamData->SetImage(frame);
                SaveImage();//Lưu hình
                return CAM_SUCCESS;
            }
        }
    }
    if(!m_pCamData->GetSubURL().empty()){
        cv::VideoCapture cap(m_pCamData->GetSubURL(), cv::VideoCaptureAPIs::CAP_GSTREAMER);
        if( cap.isOpened() )
        {
            cv::Mat frame;
            cap >> frame;
            if( !frame.empty() ) {
                m_pCamData->SetImage(frame);
                SaveImage();//Lưu hình
                return CAM_SUCCESS;
            }
            return CAM_ERROR_EMPTY_FRAME;
        }
        return CAM_ERROR_CLOSE;
    }
    return CAM_ERROR_INVALID_URL;
}


// Description: Chụp hình từ camera
// Parameters: 
//		
// Return: None
int CameraHandler::CaptureImage(CameraData* pCamData){
    SetCamdata(pCamData);
    // Chụp hình
    //pthread_create(m_thrCapture,NULL,&CaptureImage,NULL); // Đa luồng
    CaptureResult returncode = CaptureImage();
    if(returncode)
    {       
        return returncode;
    };// Đơn luồng
    // Lưu hình
    SaveImage();
}