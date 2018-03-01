/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Lớp SmartBellData chứa dữ liệu ứng dụng

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
bool SmartBellData::Initialize(){	
	// Initialize mutex
	pthread_mutex_init(&m_mutexBellDataQueue, NULL);
	bool bRes = true;
	bRes &= m_dConfig.ReadConfigParam();
	bRes &= m_dConfig.WriteConfigParam();
	return bRes;
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
		pthread_mutex_lock(&m_mutexBellDataQueue); //Lock m_qBellDataQueue
		m_qBellDataQueue.push(dBellData);
  		pthread_mutex_unlock(&m_mutexBellDataQueue); // Unlock m_qBellDataQueue
	}
}

// Description: Lấy và xóa dữ liệu đầu tiên
// Parameters: None
//		
// Return: None
BellData* SmartBellData::PopBellData()
{
	BellData * pBellData = NULL;
	pthread_mutex_lock(&m_mutexBellDataQueue); //Lock m_qBellDataQueue

	if (!m_qBellDataQueue.empty())  {
		pBellData = new BellData();
		*pBellData = m_qBellDataQueue.front();
		m_qBellDataQueue.pop();
	}
	pthread_mutex_unlock(&m_mutexBellDataQueue); // Unlock m_qBellDataQueue

	return pBellData;
}
