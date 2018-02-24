/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Quản lý thao tác của camera

*Contributors:
   Pham Chi Viet Hung:	08-Feb-2018: Initial implementation and documentation.
*****************************************/
#ifndef CLIENT_API_H_
#define CLIENT_API_H_
///****************  INCLUDE ***************///
#include "BellData.h"
#include "CameraData.h"
#include <iostream>
#include <string>
#include <cstring>
#include <curl/curl.h>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/reader.h"
///****************  DEFINE ****************///
#define NETSOFT_GET_CAMLIST_URL "http://221.132.23.2:8099/GSTB_Services/Service1.svc/getlistcam"
#define CONTENT_TYPE "content-type: application/json"
#define NETSOFT_PUSH_IMAGE_URL "http://221.132.23.2:8099/GSTB_Services/Service1.svc/push_imagepath"
///**************  NAMESPACE **************///

/*
 * Class: ClientAPI
 *
 *  Handle connect IP camera tasks
 */
class ClientAPI{

   private: 
        ///*************** FUCNTION **************///
        std::string CurlExecute(std::string url, std::string type, std::string data);
        std::vector <std::string> MessageSpliter(std::string message);
        CameraData ParseJSONObject(std::string sJSONObject);
        ///*************** VARIABLE **************///

   public:
        ///*************** FUCNTION **************///
        ClientAPI();
        virtual ~ClientAPI();
        int GetCameraList(BellData* pBellData);
        int PostImageInfo(BellData* pBellData);
        ///*************** VARIABLE **************///


};
#endif  // ClientAPI