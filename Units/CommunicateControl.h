/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Lớp CommunicateControl là lớp bao của lớp mosquitto nhằm cung cấp các giao thức gửi và nhận mesage trong IOT

*Contributors:
   Tran Dai Hiep:	01-Feb-2018: Initial implementation and documentation.
*****************************************/
#ifndef CommunicateControl_H_
#define CommunicateControl_H_
///****************  INCLUDE ***************///
#include <mosquittopp.h>
#include <functional>
///****************  DEFINE ****************///
#define BUFSIZE 201

#define POS_X 0
#define POS_Y 0
#define WIDTH 1200
#define HEIGHT 700
///**************  NAMESPACE **************///

/*
 * Class: CommunicateControl
 *
 *  Lớp CommunicateControl là lớp bao của lớp mosquitto nhằm cung cấp các giao thức gửi và nhận mesage trong IOT
 */
class CommunicateControl: public mosqpp::mosquittopp {

	
   private: //// PRIVATE
		///*************** FUCNTION **************///
		
		///*************** VARIABLE **************///

   public: //// PUBLIC
		///*************** FUCNTION **************///
		CommunicateControl(const char *id=NULL, bool clean_session=true);
		~CommunicateControl();
		std::function<void(std::string)> m_strHandlerFunction;
		void on_connect(int rc);
		void on_message(const struct mosquitto_message *message);
		void on_subscribe(int mid, int qos_count, const int *granted_qos);
		void addHandler(std::function<void(std::string)> callback);
		void publish(std::string message);
		///*************** VARIABLE **************///


};
#endif  // CommunicateControl