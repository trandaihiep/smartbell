/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Quản lý thao tác của camera

*Contributors:
   Pham Chi Viet Hung:	08-Feb-2018: Initial implementation and documentation.
*****************************************/
#ifndef CAMERA_HANDLER_H_
#define CAMERA_HANDLER_H_
///****************  INCLUDE ***************///
#include "../Serialize/CameraData.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

///****************  DEFINE ****************///
enum CaptureResult{
    CAM_SUCCESS = 0,            // Capture success
    CAM_ERROR_CLOSE,            // Cannot open camera
    CAM_ERROR_EMPTY_FRAME,      // Empty frame
    CAM_ERROR_INVALID_URL,      // Invalib url
};
#define IMAGE_DIR "/var/www/html/img/"
///**************  NAMESPACE **************///

/*
 * Class: CameraHandler
 *
 *  Handle connect IP camera tasks
 */
class CameraHandler{

   private: 
        ///*************** FUCNTION **************///
        void SetCamdata(CameraData* pCamData);
        CaptureResult CaptureImage();
        void SaveImage();
        ///*************** VARIABLE **************///
        CameraData* m_pCamData;
   public:
        ///*************** FUCNTION **************///
        CameraHandler();
        virtual ~CameraHandler();
        int CaptureImage(CameraData* pCamData);
        
        pthread_t m_thrCapture;
        ///*************** VARIABLE **************///


};
#endif  // CameraHandler