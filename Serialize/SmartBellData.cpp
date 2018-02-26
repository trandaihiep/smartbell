/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Lớp SmartBellData là lớp bao của lớp mosquitto nhằm cung cấp các giao thức gửi và nhận mesage trong IOT

*Contributors:
   Tran Dai Hiep:	01-Feb-2018: Initial implementation and documentation.
*****************************************/

///****************  INCLUDE ***************///
#include "SmartBellData.h"


///************** FUCNTION **************///
// Description: 
// Parameters: 
//		
// Return: None
SmartBellData::SmartBellData()
{
	
}
// Description: 
// Parameters: 
//		
// Return: None
SmartBellData::~SmartBellData(){

}

// Description: Khởi tạo dữ liệu
// Parameters: None
//		
// Return: true/false - Success/Failure
bool SmartBellData::Initialize()
{	bool bRes = true;
	bRes &= m_dConfig.ReadConfigParam();
	bRes &= m_dConfig.WriteConfigParam();
	return bRes;
}
// // Description: Kiểm tra tính hợp lệ của dữ liệu nhận từ chuông
// // Parameters: 
// //		string sBellData: Dữ liệu nhận từ chuông
// // Return: None
// bool SmartBellData::IsInvalidBellData(string sBellData)
// {
// 	return true;
// }

// Description: Nhận số lượng dữ liệu chuông cửa
// Parameters: None
//		
// Return: int Số lượng
int SmartBellData::BellDataSize(){ // Get number of Bell Data queue
	return m_qBellDataQueue.size();
}

// Description: Thêm dữ liệu chuông cửa vào
// Parameters: 
//		string sBellData: Dữ liệu nhận từ chuông
// Return: None
void SmartBellData::PushBellData(string sBellData)
{
	BellData dBellData;
	dBellData.ParseBellData(sBellData);
	if (dBellData.ParseBellData(sBellData)){// Kiểm tra tính hợp lệ
		m_qBellDataQueue.push(dBellData);
	}
}

// Description: Lấy và xóa dữ liệu đầu tiên
// Parameters: None
//		
// Return: None
BellData SmartBellData::PopBellData()
{
	if (!m_qBellDataQueue.empty())  {
		BellData dBellData = m_qBellDataQueue.front();
		m_qBellDataQueue.pop();
		return dBellData;
	}

	return NULL;
}
