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
	while (true)
	{
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
	// SetLogLevel(LOG_DISP_WARNING);
	// SetLogLevel(LOG_DISP_INFO);
	SetLogLevel(LOG_DISP_DEBUG);
	
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
	m_pComControl = new MQTTConnector("SmartBell1", sAppServerIP.c_str(), nPort);
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
	//Log(LOG_INFO, sLogContent);
	Log(LOG_WARNING, sLogContent);
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

	Log(LOG_WARNING, "ProcessDataQueue");
	// if (g_bProcessing) return; // Chỉ cho phép 1 luồng xử lý
	// g_bProcessing = true; 
	bool bHasBellData = true;

	while(bHasBellData){
		// Lấy dữ liệu chuông
		BellData * pBellData = g_pSmartBellData->PopBellData();
		if(pBellData != NULL){
			// Xử lý dữ liệu, chụp hình và gửi ảnh
			// ProcessBellDataCaptureImage(pBellData);
			//pthread_t thr;
			//pthread_create(&thr,NULL,ProcessBellDataCaptureImage,pBellData);
			StartCaptureImage(pBellData);
		}else{
			bHasBellData = false;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	}
	
	g_bProcessing = false;
}

// Description: Chờ xử lý dữ liệu nhận được
// Parameters: 
//		None
// Return: None
void * ProcessBellDataCaptureImage( void *args){	
// void  ProcessBellDataCaptureImage(BellData* pBellDt){

  	BellData* pBellDt = (BellData*) args;
	if(pBellDt != NULL){

		Log(LOG_INFO, "ProcessBellDataCaptureImage");
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
	return NULL;
}

// Description: Capture iamges, push path to API server
// Parameters: 
//		None
// Return: None
void  StartCaptureImage( void *args){

  	BellData* pBellDt = (BellData*) args;
	if(pBellDt != NULL){

		Log(LOG_INFO, "StartCaptureImage");
		// Lấy danh sách camera và thêm vào dữ liệu chuông
		ClientAPI dClientApi;
		dClientApi.GetCameraList(pBellDt);
		int nCameraCnt = pBellDt->GetCameraCount();
		//CameraHandler arCameraHandler[nCameraCnt];
		std::thread arThread[nCameraCnt];
		// Chụp hình
		for (int nCamIdx = 0; nCamIdx < nCameraCnt; nCamIdx++){
			CameraData dCamera = pBellDt->GetCameraData(nCamIdx);
			//CameraData *pCamData = &dCamera;
			//pthread_t thr;
			arThread[nCamIdx] = std::thread(pCaptureImage, dCamera);
			//pthread_create(&thr,NULL,pCaptureImage,dCamera);
			//arCameraHandler[nCamIdx].CaptureImage(&dCamera);
		}
		// Lấy danh sách camera và thêm vào dữ liệu chuông
		dClientApi.PostImageInfo(pBellDt);
		// Chờ đợi chụp hình
		for (int nCamIdx = 0; nCamIdx < nCameraCnt; nCamIdx++){
			arThread[nCamIdx].join();
			std::cout << "Joined thread " << nCamIdx << " ,ID: " << std::this_thread::get_id() << std::endl;
		}
		// Xóa BellData
		delete pBellDt;
	}
}


void pCaptureImage(CameraData CamDt){
// void  ProcessBellDataCaptureImage(BellData* pBellDt){
	//CameraData* pCamDt = (CameraData*) args;
	//std::cout << "Camdata: " << CamDt.GetCamID() << std::endl;
	//std::cout << "URLdata: " << CamDt.GetMainURL() << std::endl;
	CameraHandler CamHandler;
	CamHandler.CaptureImage(&CamDt);
  	std::cout << "Thread : " << std::this_thread::get_id() << std::endl;
	//return NULL;
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