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
#include <SmartBellConfig.h>
#include <pthread.h>
///****************  DEFINE ****************///

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
		pthread_mutex_t m_mutexBellDataQueue = PTHREAD_MUTEX_INITIALIZER;

		std::queue<BellData> m_qBellDataQueue;	// Queue store receiving bell data
   public: //// PUBLIC
		///*************** FUCNTION **************///
		SmartBellData();
		~SmartBellData();
		bool Initialize();
		void PushBellData(string sBellData);
		BellData* PopBellData();

		///*************** VARIABLE **************///
		SmartBellConfig m_dConfig;

};
#endif  // SmartBellData