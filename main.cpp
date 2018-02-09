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

///************** MAIN PROCESS **************///
int main(void)
{
	// Khởi tạo dữ liệu
	InitializeData();
	// Chờ nhận và xử lý dữ liệu
	ListenDataProcess();

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
	// Xóa dữ liệu đang có
	if (g_pSmartBellData != NULL ){
		delete g_pSmartBellData;
	}
	// Khởi tạo dữ liệu hệ thống
	g_pSmartBellData =  new SmartBellData();
	g_pSmartBellData.Initialize();
	// Thiết lập việc ghi log
	SetLogLevel(LOG_DISP_INFO);


		int rc = 0;
	::g_pSmartBellData.m_bAlarmFlag = false;
	vector<int> compression_params;
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
        compression_params.push_back(9);
	std::string input;
	std::cout << "Main : " << std::this_thread::get_id() << std::endl;
	std::time_t result = std::time(nullptr);
        std::cout << std::asctime(std::localtime(&result)) << std::endl;
	cout << "MQTT server: " << SERVER << \
			" port: " << PORT << std::endl << \
		 	"Subscribe topic: " << GWTOPIC << std::endl << \
			"Publish topic: " << ALARMTOPIC << std::endl << \
			"Sensor ID: " << SENSORID << std::endl;
	mosqpp::lib_init();
	m_pComControl = new CommunicateControl("m_pComControl", SERVER, PORT);
	m_pComControl->addHandler(&ReceiveHandler);
	m_pComControl->loop_start();

}

// Description: Chờ xử lý dữ liệu nhận được
// Parameters: 
//		None
// Return: None
void ListenDataProcess(){	
	while(1){
		if(g_pSmartBellData.m_bAlarmFlag){
			time_t rawtime;
			struct tm * timeinfo;
  			char buffer[80];
  			time (&rawtime);
  			timeinfo = localtime(&rawtime);
  			strftime(buffer,sizeof(buffer),"%d%m%Y-%H%M%S",timeinfo);
  			std::string str(buffer);
			std::cout << "ALARM!" << std::endl;
			std::cout << "Connecting URL: " << URL << std::endl;
			cv::VideoCapture cap(URL, cv::VideoCaptureAPIs::CAP_GSTREAMER);
			if( !cap.isOpened() )
			{
				std::cout << "Not good, open camera failed" << std::endl;
				std::cout << "URL: " << input << std::endl;
				return 0;
			}
			cv::Mat frame;
			cap >> frame;
			if( frame.empty() ) {
				std::cout << "Empty Frame" << std::endl;
				continue;
			}
			//imshow("Live streaming...", frame);
			//char c = (char)waitKey(10);
			std::string tmp = IMG_PATH + str + ".png"; cout << tmp << endl;
			imwrite(tmp, frame, compression_params);
			tmp = PUB_MESSAGE + str + ".png\"}";	cout << tmp << endl;
			m_pComControl->publish(tmp);
			g_pSmartBellData.m_bAlarmFlag = false;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

// Description: Giải phóng bộ nhớ
// Parameters: 
//		None
// Return: None
void ReleaseData(){	
	if (m_pComControl != NULL){
		m_pComControl->disconnect();
		m_pComControl->loop_stop();
		delete m_pComControl
	}
	mosqpp::lib_cleanup();
}


// Description: Xử lý dữ liệu nhận được
// Parameters: 
//		std::string sReceiveData - Dữ liệu nhận được
// Return: None
void ReceiveHandler(std::string sReceiveData){
	time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];
        time (&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer,sizeof(buffer),"%d%m%Y-%H%M%S",timeinfo);
        std::string str(buffer);
	cout << str  << " | Get: " << sReceiveData << endl;
	int val = 0;
	std::vector<std::string> vect;
	vect = split(t,';');				//cout<<"Size : " << vect.size() << vect.at(4) << endl; // vect.at(4) => SS00117D8D7E070,-59,99,2,6414
	if (vect.size() > 5){																					//	^ this is Sensor ID		  ^ sensor value
		vect=split(vect.at(4),',');		// split vect.at(4) by "," into 4 elements where .at(0) is sensor ID and .at(4) is value of sensor
		if ((vect.size() > 4) & (!strcmp(vect.at(0).c_str(), SENSORID)))
		{
			val = std::stoi(vect.at(4));	cout<<"Val: " << val << endl;			
			if(val > THRES){
				g_pSmartBellData.m_bAlarmFlag = true;
			}
		}
	}
}