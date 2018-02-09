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


///****************  DEFINE ****************///
#define SERVER "10.4.1.210"
#define PORT 1883
#define GWTOPIC "/SCPCloud/DEVICE/FD445E29"		//Where to collect sensor data
#define ALARMTOPIC "/SCPCloud/DEVICE/509a4c5912d3"	//Where to push warning to server
#define SENSORID "SS00122F5E0A200"// ID of sound sensor
#define URL "rtspsrc location=\"rtsp://14.161.3.247/axis-media/media.amp\" latency=0 ! decodebin ! videoconvert ! appsink"
#define PUB_MESSAGE "{\"urlCam\":\"http://ansvhcm.vn:41092/img/"
#define IMG_PATH "/var/www/html/img/"
///**************  NAMESPACE **************///
using namespace std;

/*
 * Class: SmartBellData
 *
 *  Lớp SmartBellData là lớp chứa dữ liệu của chương trình
 */
class SmartBellData{
   private: //// PRIVATE
		///*************** FUCNTION **************///
		
		///*************** VARIABLE **************///
		std::string m_sServerIP 	= SERVER 	// Địa chỉ IP của server
		int 		m_nPort 		= PORT		// Port
		std::string m_sGwTopic 		= GWTOPIC	//Where to collect sensor data
		std::string m_sAlarmTopic 	= ALARMTOPIC //Where to push warning to server
		std::string m_sSensorID 	= SENSORID// ID of sound sensor
		std::string m_sUrl 			= URL
		std::string m_sMessage 		= PUB_MESSAGE
		std::string m_sImagePath 	= IMG_PATH
   public: //// PUBLIC
		///*************** FUCNTION **************///
		SmartBellData();
		~SmartBellData();
		std::string GetServerIP(){
			return m_sServerIP;
		};
		void SetServerIP(std::string sServerIP){
			m_sServerIP = m_sServerIP;
		};
		///*************** VARIABLE **************///
		bool m_bAlarmFlag = false // Cờ khi nhận dữ liệu

};
#endif  // SmartBellData