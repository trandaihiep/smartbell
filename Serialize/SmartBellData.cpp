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
#include "Units/SmartBellData.h"


///************** FUCNTION **************///
// Description: 
// Parameters: 
//		
// Return: None
SmartBellData::SmartBellData()
{
	
	int keepalive = 60;
	/* Connect immediately. This could also be done by calling
	 * mqtt_tempconv->connect(). */
	connect(host, port, keepalive);
};

SmartBellData::~SmartBellData(){

}
