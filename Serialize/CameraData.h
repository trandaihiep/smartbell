/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Lop chua data cho camera

*Contributors:
   Pham Chi Viet Hung:	08-Feb-2018: Initial implementation and documentation.
*****************************************/
#ifndef CameraData_H_
#define CameraData_H_
///****************  INCLUDE ***************///
#include<string>
#include <opencv2/core.hpp>
#include <vector>
///****************  DEFINE ****************///

///**************  NAMESPACE **************///

/*
 * Class: CameraData
 *
 *  Lop chua data cho camera
 */
class CameraData {

   private: //// PRIVATE
        ///*************** FUCNTION **************///

        ///*************** VARIABLE **************///
        std::string m_sBellID;
        std::string m_sCamID;
        std::string m_sMainURL;
        std::string m_sSubURL;
        std::string m_sPath;
        cv::Mat m_mImage;
   public: //// PUBLIC
        ///*************** FUCNTION **************///
       CameraData();
       virtual ~CameraData();
       std::string GetBellID();
       void SetBellID(std::string sBellID);
       std::string GetCamID();
       void SetCamID(std::string sCameID);
       std::string GetMainURL();
       void SetMainURL(std::string sMainURL);
       std::string GetSubURL();
       void SetSubURL(std::string sSubURL);
       std::string GetPath();
       void SetPath(std::string sPath);
       cv::Mat GetImage();
       void SetImage(cv::Mat dImage);
        ///*************** VARIABLE **************///
        std::vector<int> compression_params;
};
#endif