/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Xử lý tác vụ của camera

*Contributors:
   Pham Chi Viet Hung:	08-Feb-2018: Initial implementation and documentation.
*****************************************/

///****************  INCLUDE ***************///
#include "ClientAPI.h"

///************** FUCNTION **************///
// Description: Contructor
// Parameters: 
//		
// Return: None
ClientAPI::ClientAPI(){
	m_pCamData = NULL;

}
///************** FUCNTION **************///
// Description: Decontructor
// Parameters: 
//		
// Return: None
ClientAPI::~ClientAPI(){

}

// Description: Nhận thông tin camera từ server và thêm vào pBellData
// Parameters: 
//		BellData* pBellData: Con trỏ dữ liệu chuông cửa
// Return: None
void ClientAPI::GetCameraList(BellData* pBellData){
    if (pBellData == NULL)
        return;
}

// Description: Gửi thông tin và hình ảnh chụp được lên server
// Parameters: 
//		BellData* pBellData: Con trỏ dữ liệu chuông cửa
// Return: None
void ClientAPI::PostImageInfo(BellData* pBellData){
    if (pBellData == NULL)
        return;
}