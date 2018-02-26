/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Lop chua data cho camera

*Contributors:
   Pham Chi Viet Hung:	08-Feb-2018: Initial implementation and documentation.
*****************************************/
#ifndef BELLDATA_H_
#define BELLDATA_H_
///****************  INCLUDE ***************///
#include<string>
#include"CameraData.h"
#include<iostream>
#include <vector>
///****************  DEFINE ****************///

///**************  NAMESPACE **************///

/*
 * Structure: BellInfo
 *  Thông tin định danh chuông cửa
 *  
 */
struct BellInfo {
    std::string sBellID = "";
    unsigned int nRSS = 0;
    unsigned int nValue = 0;
};
/*
 * Class: BellData
 *
 *  Lop chua data cho camera
 */
class BellData {

   private: //// PRIVATE
        ///*************** FUCNTION **************///
std::vector<std::string> Split (const std::string input,char delim);

        ///*************** VARIABLE **************///
        BellInfo m_dBellInfo;
        unsigned int m_unCameraCnt = 0; // Số lượng camera
        std::vector <CameraData> m_arpCameraData;
   public: //// PUBLIC
        ///*************** FUCNTION **************///
        BellData();
        // BellData(std::string sBellData);
        virtual ~BellData();
        bool ParseBellData(std::string sBellData); //Phân tích chuối dữ liệu sBellData sau đó lưu dữ liệu nếu hợp lệ.

        BellInfo GetBellInfo(); // Lấy thông tin chuông
        unsigned int GetCameraCount();   // Lấy số lượng camera được điều khiển bởi chuông
        CameraData GetCameraData(unsigned int unCameraIndex);
        bool AddCameraData(CameraData dCamDt);
        // bool RemoveCameraData(unsigned int unCameraIndex);

        ///*************** VARIABLE **************///
};
#endif