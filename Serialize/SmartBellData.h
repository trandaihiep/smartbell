/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Lớp SmartBellData là lớp chứa dữ liệu của chương trình
*Contributors:
   Tran Dai Hiep:	01-Feb-2018: Initial implementation and documentation.
*****************************************/
#ifndef SmartBellData_H_
#define SmartBellData_H_
///****************  INCLUDE ***************///
#include<string>
#include<queue>
#include <BellData.h>
///****************  DEFINE ****************///
#define APP_SERVER "10.4.1.210"
#define APP_PORT 1883
#define GW_LISTEN "/SCPCloud/DEVICE/FD445E29"		//Where to collect sensor data
#define GW_ALARM "/SCPCloud/DEVICE/509a4c5912d3"	//Where to push warning to server

#define IMG_DIR_PATH "/var/www/html/img/"
#define CONFIG_FILE_PATH "~/.smartbell/config"
///**************  NAMESPACE **************///
using namespace std;
/*
 * Structure: SmartBellConfig
 *  Các thiết lập của phần mềm
 *  
 */
class SmartBellConfig{
	public:
		std::string sAppIP 	= APP_SERVER;	// Aplication IP (Netsoft server IP)
		int 		nPort 	= APP_PORT;	// Port (Netsoft port)
		std::string sGateWayListenAdr 	= GW_LISTEN;	//GateWay listen address
		std::string sGateWayAlarmAdr 	= GW_ALARM; //GateWay publish address
		std::string sImagePath	 		= IMG_DIR_PATH;// Direction path, where store image
		std::string sConfigFilePath	 	= CONFIG_FILE_PATH;// Direction path, where store image
		bool ReadConfigParam(string sConfigFilePath = CONFIG_FILE_PATH){

			return true;
		};
		bool WriteConfigParam(){

			return true;
		};
};
/*
 * Class: SmartBellData
 *
 *  Lớp SmartBellData là lớp chứa dữ liệu của chương trình
 */
class SmartBellData{
   private: //// PRIVATE
		///*************** FUCNTION **************///

		///*************** VARIABLE **************///
		std::queue<BellData> m_qBellDataQueue;	// Queue store receiving bell data
   public: //// PUBLIC
		///*************** FUCNTION **************///
		SmartBellData();
		~SmartBellData();
		bool Initialize();
		int BellDataSize(); // Get number of Bell Data queue
		void PushBellData(string sBellData);
		BellData PopBellData();

		///*************** VARIABLE **************///
		SmartBellConfig m_dConfig;

};
#endif  // SmartBellData