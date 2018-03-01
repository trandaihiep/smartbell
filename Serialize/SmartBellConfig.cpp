/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Lớp SmartBellConfig đọc và ghi thiết lập của ứng dụng

*Contributors:
   Tran Dai Hiep:	01-Feb-2018: Initial implementation and documentation.
*****************************************/

///****************  INCLUDE ***************///
#include "SmartBellConfig.h"


///************** FUCNTION **************///
// Description: 
// Parameters: 
//		
// Return: None
SmartBellConfig::SmartBellConfig(string sConfigFilePath /*= CONFIG_FILE_PATH*/)
						:Config(sConfigFilePath)
{
	InitValue(APP_PORT_KEY,std::to_string(APP_PORT_VAL));
	InitValue(APP_SERVER_KEY,APP_SERVER_VAL);
	InitValue(GW_ALARM_KEY,GW_ALARM_VAL);
	InitValue(GW_LISTEN_KEY,GW_LISTEN_VAL);
	InitValue(IMG_DIR_PATH_KEY,IMG_DIR_PATH_VAL);

	m_sConfigFilePath = sConfigFilePath;
}
// Description: 
// Parameters: 
//		
// Return: None
SmartBellConfig::~SmartBellConfig(){

}

// Description: Đọc thông số thiết lập
// Parameters: None
//		
// Return: true/false - Success/Failure
bool SmartBellConfig::ReadConfigParam(){	
	ReadConfig();
	sAppIP 				= GetString(APP_SERVER_KEY);	// Aplication IP (Netsoft server IP)
	nPort 				= GetInt(APP_PORT_KEY);	// Port (Netsoft port)
	sGateWayListenAdr 	= GetString(GW_LISTEN_KEY);	//GateWay listen address
	sGateWayAlarmAdr 	= GetString(GW_ALARM_KEY); //GateWay publish address
	sImagePath	 		= GetString(IMG_DIR_PATH_KEY);// Direction path, where store image

	return true;
}
// Description: Thêm dữ liệu chuông cửa vào
// Parameters: 
//		string sBellData: Dữ liệu nhận từ chuông
// Return: None
bool SmartBellConfig::WriteConfigParam()
{

	return true;
}
