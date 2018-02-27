/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

**************  DESCRIPTION **************
Hiện thực xử lý cho Main proces

Contributors:
   Tran Dai Hiep:	01-Feb-2018: Initial implementation and documentation.
*****************************************/

#include "main.h"
#include "ClientAPI.h"

LogHandler g_sLog;
extern SmartBellData*    g_pSmartBellData ;   // Application data
extern bool           	g_bProcessing;    // Cờ báo việc đang xử lý dữ liệu
extern MQTTConnector *  	m_pComControl;
  
///************** MAIN PROCESS **************///
int main(void)
{
	Log(LOG_INFO, "Start!!!");
	// Khởi tạo dữ liệu
	InitializeData();
	// Xử lý dữ liệu
	ProcessDataQueue();
	//Chờ nhận
	while (true){
		std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::hours(std::numeric_limits<int>::max()));
	}
	// Giải phóng bộ nhớ khi kết thúc việc xử lý
	ReleaseData();
	return 0;
}

///************** FUCNTION **************///

// Description: Xử lý dữ liệu nhận được
// Parameters: 
//		std::string sReceiveData - Dữ liệu nhận được
// Return: 0 (Success)/ other (Failure)
void InitializeData(){
	// Thiết lập việc ghi log

	Log(LOG_INFO, "InitializeData...");
	SetLogLevel(LOG_DISP_INFO);
	// Xóa dữ liệu đang có
	if (g_pSmartBellData != NULL ){
		delete g_pSmartBellData;
	}
	// Khởi tạo dữ liệu hệ thống
	g_pSmartBellData =  new SmartBellData();
	g_pSmartBellData->Initialize();
	g_bProcessing =  false;
	// Khởi tạo kết nối MQTT
	mosqpp::lib_init();
	std::string sAppServerIP = g_pSmartBellData->m_dConfig.sAppIP;

	int nPort = g_pSmartBellData->m_dConfig.nPort;
	m_pComControl = new MQTTConnector("SmartBell", sAppServerIP.c_str(), nPort);
	m_pComControl->SetGWListenAdr(g_pSmartBellData->m_dConfig.sGateWayListenAdr);
	m_pComControl->SetGWAlarmAdr(g_pSmartBellData->m_dConfig.sGateWayAlarmAdr);
	m_pComControl->addHandler(&ReceiveHandler);
	m_pComControl->loop_start();

	std::string sLogContent = "IP Server: " + sAppServerIP;
	sLogContent += "\nPort: " + std::to_string(nPort);
	sLogContent += "\nGW Listen: " + g_pSmartBellData->m_dConfig.sGateWayListenAdr;
	sLogContent += "\nGW Alarm: " + g_pSmartBellData->m_dConfig.sGateWayAlarmAdr;
	Log(LOG_INFO,sLogContent);

}

// Description: Xử lý dữ liệu nhận được
// Parameters: 
//		std::string sReceiveData - Dữ liệu nhận được
// Return: None
void ReceiveHandler(std::string sReceiveData){
	std::string sLogContent = "Receive: " + sReceiveData;
	Log(LOG_INFO, sLogContent);
	// Add to queue
	g_pSmartBellData->PushBellData (sReceiveData);
	// Xử lý dữ liệu
	ProcessDataQueue();
}

// Description: Chờ xử lý dữ liệu nhận được
// Parameters: 
//		None
// Return: None
void ProcessDataQueue(){	

	Log(LOG_INFO, "ProcessDataQueue");
	if (g_bProcessing) return; // Chỉ cho phép 1 luồng xử lý
	g_bProcessing = true; 

	while(g_pSmartBellData->BellDataSize() != 0){
		// Lấy dữ liệu chuông
		BellData dBellDt = g_pSmartBellData->PopBellData();
		BellData * pBellData = new BellData();
		*pBellData = dBellDt;
		if(pBellData != NULL){
			// Xử lý dữ liệu, chụp hình và gửi ảnh
			ProcessBellDataCaptureImage(pBellData);
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));

	}
	
	g_bProcessing = false;
}

// Description: Chờ xử lý dữ liệu nhận được
// Parameters: 
//		None
// Return: None
//void * ProcessBellDataCaptureImage( void *args){	
void  ProcessBellDataCaptureImage(BellData* pBellDt){
	if(pBellDt != NULL){
		// Lấy danh sách camera và thêm vào dữ liệu chuông
		ClientAPI dClientApi;
		dClientApi.GetCameraList(pBellDt);
		int nCameraCnt = pBellDt->GetCameraCount();
		CameraHandler arCameraHandler[nCameraCnt];
		
		// Chụp hình
		for (int nCamIdx = 0; nCamIdx < nCameraCnt; nCamIdx++){
			CameraData dCamera = pBellDt->GetCameraData(nCamIdx);
			arCameraHandler[nCamIdx].CaptureImage(&dCamera);
		}

		// Chờ đợi chụp hình
		// for (int nCamIdx = 0; nCamIdx < nCameraCnt; nCamIdx++){
		// 	pthread_join(arCameraHandler[nCamIdx].m_thrCapture);
		// }
		
		// Lấy danh sách camera và thêm vào dữ liệu chuông
		dClientApi.PostImageInfo(pBellDt);
		// Xóa BellData
		delete pBellDt;
	}
}

// Description: Giải phóng bộ nhớ
// Parameters: 
//		None
// Return: None
void ReleaseData(){	
	// Xóa dữ liệu chương trình
	if (g_pSmartBellData != NULL ){
		delete g_pSmartBellData;
	}
	
	if (m_pComControl != NULL){
		m_pComControl->disconnect();
		m_pComControl->loop_stop();
		delete m_pComControl;
	}
	mosqpp::lib_cleanup();
}

// Description: Hiển thị và lưu lại thông tin
// Parameters: 
//		int nLogLevel: Cấp độ ghi thông tin 
//      const char *pztcContent : Nội dung
//      string      sContent    : Nội dung
// Return: None
void Log(int nLogLevel, const char *pztcContent){
    g_sLog.Log(nLogLevel, pztcContent);

}
void Log(int nLogLevel, std::string sContent){
    g_sLog.Log(nLogLevel, sContent);
}
// Description: Thiết lấp mức độ hiển thị thông tin
// Parameters: 
//		int nLogLevel: Cấp độ ghi thông tin 
// Return: None
void SetLogLevel(int nLogLevel){
    g_sLog.SetDispMode(nLogLevel);
}
