/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Quản lý thao tác của camera

*Contributors:
   Tran Dai Hiep:	03-Feb-2018: Initial implementation and documentation.
*****************************************/
#ifndef CAMERA_HANDLER_H_
#define CAMERA_HANDLER_H_
///****************  INCLUDE ***************///
#include "Logging.h"
///****************  DEFINE ****************///

///**************  NAMESPACE **************///

/*
 * Class: CameraHandler
 *
 *  Quản lý thao tác của camera
 */
class CameraHandler: public VideoCapture {

    
   private: //// PRIVATE
        ///*************** FUCNTION **************///
        CameraData* m_CamDt;
        ///*************** VARIABLE **************///

   public: //// PUBLIC
        ///*************** FUCNTION **************///
        CameraHandler();
        virtual ~CameraHandler();
        void SetCamdata();
        
        void CaptureImage(const char* pztcFilePath); // Chụp hình từ máy quay
        ///*************** VARIABLE **************///


};
#endif  // CameraHandler