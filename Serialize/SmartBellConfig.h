/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Lớp SmartBellConfig là lớp chứa dữ liệu của chương trình
*Contributors:
   Tran Dai Hiep:	01-Feb-2018: Initial implementation and documentation.
*****************************************/
#ifndef SmartBellConfig_H_
#define SmartBellConfig_H_
///****************  INCLUDE ***************///
#include <Config.h>
///****************  DEFINE ****************///
#define APP_PORT_KEY "Port"
#define APP_PORT_VAL 1883
#define APP_SERVER_KEY "IP"
#define APP_SERVER_VAL "123.20.207.35"
#define GW_ALARM_KEY "GatewayAlarm"	//Where to push warning to server
#define GW_ALARM_VAL "/SCPCloud/DEVICE/509a4c5912d3"	//Where to push warning to server
#define GW_LISTEN_KEY "GatewayListen"
#define GW_LISTEN_VAL "/vnpt/hcm/bell/#"
#define IMG_DIR_PATH_KEY "ImagePath"
#define IMG_DIR_PATH_VAL "/var/www/html/img/"
#define CONFIG_FILE_PATH "/etc/smartbell/config.cfg"

///**************  NAMESPACE **************///
using namespace std;
/*
 * Structure: SmartBellConfig
 *  Các thiết lập của phần mềm
 *  
 */
class SmartBellConfig: public Config{
	private:
		std::string m_sConfigFilePath	= CONFIG_FILE_PATH;// Direction path, where store image

	public:
		std::string sAppIP 				= APP_SERVER_VAL;	// Aplication IP (Netsoft server IP)
		int 		nPort 				= APP_PORT_VAL;	// Port (Netsoft port)
		std::string sGateWayListenAdr 	= GW_LISTEN_VAL;	//GateWay listen address
		std::string sGateWayAlarmAdr 	= GW_ALARM_VAL; //GateWay publish address
		std::string sImagePath	 		= IMG_DIR_PATH_VAL;// Direction path, where store image
		SmartBellConfig(string sConfigFilePath = CONFIG_FILE_PATH);
		~SmartBellConfig();

		bool ReadConfigParam();
		bool WriteConfigParam();
};
#endif  // SmartBellConfig