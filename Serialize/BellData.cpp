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
    m_dBellInfo.sBellID   = "SS00122F5E0A202";
    m_dBellInfo.nRSS      = 0;
    m_dBellInfo.nValue    = 1;
    m_unCameraCnt = 0; 
    m_arpCameraData = NULL;
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
    if (m_arpCameraData == NULL){
        delete [] m_arpCameraData;
    }
}

// Description: Phân tích chuối dữ liệu sBellData sau đó lưu dữ liệu nếu hợp lệ.
// Parameters: 
//      string sBellData: Dữ liệu nhận từ chuông
// Return: 
//      true: Dữ liệu hợp lệ, lưu dữ liệu mới
//      false: Dữ liệu không hợp lệ
bool BellData::ParseBellData(std::string sBellData){
	// int val = 0;
	// std::vector<std::string> vect;
	// vect = split(t,';');				//cout<<"Size : " << vect.size() << vect.at(4) << endl; // vect.at(4) => SS00117D8D7E070,-59,99,2,6414
	// if (vect.size() > 5){																					//	^ this is Sensor ID		  ^ sensor value
	// 	vect=split(vect.at(4),',');		// split vect.at(4) by "," into 4 elements where .at(0) is sensor ID and .at(4) is value of sensor
	// 	if ((vect.size() > 4) & (!strcmp(vect.at(0).c_str(), SENSORID)))
	// 	{
	// 		val = std::stoi(vect.at(4));	cout<<"Val: " << val << endl;			
	// 		if(val > THRES){
	// 			g_pSmartBellData.m_bAlarmFlag = true;
	// 		}
	// 	}
	// }
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
  return 2;
  //return m_unCameraCnt;
}
// Description: 
// Parameters: 
//
// Return: None
CameraData BellData::GetCameraData(unsigned int unCameraIndex){
    // if (unCameraIndex < m_unCameraCnt)){
    //     CameraData dResDt = *m_arpCameraData[unCameraIndex];
    //     return dResDt;
    // }else{
    //     return NULL;
    // }
    CameraData dumpCameraData;
    
    return dumpCameraData;
}
// Description: Thêm dữ liệu camera
// Parameters: 
//
// Return: None
bool BellData::AddCameraData(CameraData dCamDt){
    // unsigned int  unCameraCntNew = m_unCameraCnt;
    // unCameraCntNew++;
    // CameraData * arpCameraDataNew = new CameraData[unCameraCntNew];
    // // Copy old data
    // for ( int nCamIndex = 0; nCamIndex <m_unCameraCnt; nCamIndex ++ ){
    //     *arpCameraDataNew[nCamIndex] = *m_arpCameraData[nCamIndex];
    // }
    // // Add new data
    // *arpCameraDataNew[unCameraCntNew-1] = dCamDt;
    // // Delete old data
    // if (m_arpCameraData == NULL){
    //     delete [] m_arpCameraData;
    // }
    // // Update variable
    // m_arpCameraData = arpCameraDataNew;
    // m_unCameraCnt = unCameraCntNew;
    std::cout << "[BellData]Adding camera Data..." << std::endl;
    std::cout << "[BellData]BellID: " << dCamDt.GetBellID() << std::endl;
    std::cout << "[BellData]CamID: " << dCamDt.GetCamID() << std::endl;
    std::cout << "[BellData]MainURL: " << dCamDt.GetMainURL() << std::endl;
    std::cout << "[BellData]SubURL: " << dCamDt.GetSubURL() << std::endl;
    return true;
}

// // Description: 
// // Parameters: 
// //
// // Return: None
// bool BellData::RemoveCameraData(unsigned int unCameraIndex){
//   m_sMainURL = sMainURL;
// }