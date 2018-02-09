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
#define ERR_CAP_CLOSE 0x01  //Cap not open
#define ERR_EMPTY_FRAME 0x02  //Empty frame
#define ERR_EMPTY_URL 0x04
#define ERR_NUM_4 0x08
///**************  NAMESPACE **************///

/*
 * Class: CameraHandler
 *
 *  Handle connect IP camera tasks
 */
class CameraHandler{

   private: 
        ///*************** FUCNTION **************///
        
        ///*************** VARIABLE **************///
        CameraData* m_pCamData;
   public:
        ///*************** FUCNTION **************///
        CameraHandler();
        virtual ~CameraHandler();
        void SetCamdata(CameraData* pCamData);
        
        int CaptureImage();
        int SaveImage();
        ///*************** VARIABLE **************///


};
#endif  // CameraHandler