/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
This file contain camera data and provide data access methods

*Contributors:
   Pham Chi Viet Hung:	01-Feb-2018: Initial implementation and documentation.
*****************************************/
///****************  INCLUDE ***************///
#include "BellData.h"

/*
 * Class: BellData
///************** FUCNTION **************///
// Description: Contructor
// Parameters: 
//
// Return: None
BellData::BellData(){
    m_dBellInfo.sBellID   = "";
    m_dBellInfo.nRSS      = 0;
    m_dBellInfo.nValue    = 0;
    m_unCameraCnt = 0; 
    m_arpCameraData.clear();
}
// BellData::BellData(std::string sBellData){
//     m_dBellInfo.sBellID   = "";
//     m_dBellInfo.nRSS      = 0;
//     m_dBellInfo.nValue    = 0;
//     m_unCameraCnt = 0; 
//     m_arpCameraData = NULL;
//     ParseBellData(sBellData);

// }
///************** FUCNTION **************///
// Description: Decontructor
// Parameters: 
//
// Return: None
BellData::~BellData(){
    m_arpCameraData.clear();
}

// Description: Phân tích chuối dữ liệu sBellData sau đó lưu dữ liệu nếu hợp lệ.
// Parameters: 
//      string sBellData: Dữ liệu nhận từ chuông
// Return: 
//      true: Dữ liệu hợp lệ, lưu dữ liệu mới
//      false: Dữ liệu không hợp lệ
// Message Sample:  $SS00122F5E0A200,59,1#
bool BellData::ParseBellData(std::string sBellData){
	// int val = 0;
    if(sBellData[0] == '$')
    {
        std::vector<std::string> vect;
        std::size_t sz;
        vect = Split(sBellData,',');
        if (vect.size() == 3){
            m_dBellInfo.sBellID = vect[0].substr(1);
            m_dBellInfo.nRSS = std::stoi(vect[1],&sz);
            m_dBellInfo.nValue = std::stoi(vect[2],&sz);
        }
    }
    return true;
}
// Description: Lấy thông tin chuông
// Parameters: None
//
// Return: None
BellInfo BellData::GetBellInfo(){
    return m_dBellInfo;
}
// Description: Lấy số lượng camera được điều khiển bởi chuông
// Parameters: None
//
// Return: None
unsigned int BellData::GetCameraCount(){
    return m_unCameraCnt;
}
// Description: Return CameraData from array, start from 0
// Parameters: 
//
// Return: None
CameraData BellData::GetCameraData(unsigned int unCameraIndex){
    return m_arpCameraData[unCameraIndex];
}
// Description: Thêm dữ liệu camera
// Parameters: 
//
// Return: None
bool BellData::AddCameraData(CameraData dCamDt){

	Log(LOG_INFO, "BellData::AddCameraData");
	Log(LOG_INFO, dCamDt.GetBellID() );
	Log(LOG_INFO, dCamDt.GetCamID());
	Log(LOG_INFO, dCamDt.GetMainURL());
	Log(LOG_INFO, dCamDt.GetSubURL());
    
    m_unCameraCnt++;
    m_arpCameraData.push_back(dCamDt);
    return true;
}

// // Description: 
// // Parameters: 
// //
// // Return: None
// bool BellData::RemoveCameraData(unsigned int unCameraIndex){
//   m_sMainURL = sMainURL;
// }

// // Description: Split string into parts by a delimiter
// // Parameters: 
// //
// // Return: None
std::vector<std::string> BellData::Split (const std::string input,char delim)
{
	std::vector<std::string> tokens;
	std::string word;
    std::stringstream stream(input);
    while( getline(stream, word, delim) ){
        tokens.push_back(word);
	}
	return tokens;
}