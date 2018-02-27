/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Lớp MQTTConnector là lớp bao của lớp mosquitto nhằm cung cấp các giao thức gửi và nhận mesage trong IOT

*Contributors:
   Tran Dai Hiep:	01-Feb-2018: Initial implementation and documentation.
*****************************************/
#ifndef MQTTConnector_H_
#define MQTTConnector_H_
///****************  INCLUDE ***************///
#include <mosquittopp.h>
#include <functional>
#include <string>

#include "Logging.h"
///****************  DEFINE ****************///
#define BUFSIZE 201

#define POS_X 0
#define POS_Y 0
#define WIDTH 1200
#define HEIGHT 700
///**************  NAMESPACE **************///

/*
 * Class: MQTTConnector
 *
 *  Lớp MQTTConnector là lớp bao của lớp mosquitto nhằm cung cấp các giao thức gửi và nhận mesage trong IOT
 */
class MQTTConnector: public mosqpp::mosquittopp {

	
   private: //// PRIVATE
		///*************** FUCNTION **************///
		
		///*************** VARIABLE **************///
		std::string m_sGateWayListenAdr	= "";	//GateWay listen address
		std::string m_sGateWayAlarmAdr 	= ""; 	//GateWay publish address
   public: //// PUBLIC
		///*************** FUCNTION **************///
		MQTTConnector(const char *id, const char *host, int port);
		~MQTTConnector();
		std::function<void(std::string)> m_strHandlerFunction;
		void on_connect(int rc);
		void on_message(const struct mosquitto_message *message);
		void on_subscribe(int mid, int qos_count, const int *granted_qos);
		void addHandler(std::function<void(std::string)> callback);
		void publish(std::string message);


		std::string GetGWListenAdr(){ return m_sGateWayListenAdr;};
		void SetGWListenAdr( std::string sGateWayListenAdr){
			m_sGateWayListenAdr	= sGateWayListenAdr;	//GateWay listen address
		};
		
		std::string GetGWAlarmAdr(){ return m_sGateWayAlarmAdr;};
		void SetGWAlarmAdr( std::string sGateWayAlarmAdr){
			m_sGateWayAlarmAdr	= sGateWayAlarmAdr;	//GateWay publish address
		};

		///*************** VARIABLE **************///


};
#endif  // MQTTConnector