/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Xử lý tác vụ của camera

*Contributors:
   Pham Chi Viet Hung:	08-Feb-2018: Initial implementation and documentation.
*****************************************/

///****************  INCLUDE ***************///
#include "ClientAPI.h"
#include <iostream>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}   

///************** FUCNTION **************///
// Description: Contructor
// Parameters: 
//		
// Return: None
ClientAPI::ClientAPI(){
	//m_pCamData = NULL;

}
///************** FUCNTION **************///
// Description: Decontructor
// Parameters: 
//		
// Return: None
ClientAPI::~ClientAPI(){

}

// Description: Nhận thông tin camera từ server và thêm vào pBellData
// Parameters: 
//		BellData* pBellData: Con trỏ dữ liệu chuông cửa
// Return: None
int ClientAPI::GetCameraList(BellData* pBellData){
    if (pBellData == NULL)
        return 1;
    std::string jsonMessage = CurlExecute(NETSOFT_GET_CAMLIST_URL,
                                          CONTENT_TYPE,
                                         "{\"id_Bell\":\"" + pBellData->GetBellInfo().sBellID + "\"}");
    if(!jsonMessage.empty())
    {
        std::vector <std::string> objectList = MessageSpliter(jsonMessage);
         for (unsigned int i = 0; i < objectList.size();i++)
        {
            //std::cout << "Add " << i << " :" << objectList[i] << std::endl;
            pBellData->AddCameraData(ParseJSONObject(objectList[i]));
        }
    }
    return 0;
    
}

// Description: Gửi thông tin và hình ảnh chụp được lên server
// Parameters: 
//		BellData* pBellData: Con trỏ dữ liệu chuông cửa
// Return: None
int ClientAPI::PostImageInfo(BellData* pBellData){
    if (pBellData == NULL)
        return 1;
    for(unsigned int i=0; i < pBellData->GetCameraCount(); i++)
    {
        std::string tempString = "{\"id_Bell\":\"" + pBellData->GetBellInfo().sBellID + "\", "
                              "\"id_Cam\":\"" + pBellData->GetCameraData(i).GetCamID() + "\", "
                              "\"image_Path\":\"" + pBellData->GetCameraData(i).GetPath() +"\"}";
        std::string jsonMessage = CurlExecute(NETSOFT_PUSH_IMAGE_URL,
                                            CONTENT_TYPE,
                                            tempString);
        std::cout << "[ClientAPI]Push status: " << jsonMessage << std::endl;
    }
  return 0;
}

// Description: Split message into string vector, each string is an JSON object
// Parameters:
//		std::string message: data retrieve from NetSoft's API
// Return: None

std::vector <std::string> ClientAPI::MessageSpliter(std::string message)
{
    std::vector <std::string> retVector;

    std::size_t firstPos = message.find("{", 1);
    
    while(firstPos != std::string::npos){
    //std::cout << "Found at :" << firstPos << std::endl;
    std::size_t lastPos = message.find("}",firstPos+1);
    retVector.push_back(message.substr(firstPos,lastPos - firstPos+1));
    message = message.substr(lastPos+ 1, message.length());
    firstPos = message.find("{", 1);
    //std::cout << "Remain string: " << message << std::endl;
    }
    // for(int i = 0 ; i< retVector.size(); i++)
    //std::cout << "Object quantity : "<< retVector.size()<< std::endl;
    return retVector;
}

// Description: Parse each JSON Object and assign data from it to CameraData
// Parameters:
//		
// Return: None
CameraData ClientAPI::ParseJSONObject(std::string sJSONObject)
{
    //std::cout << "Handling object: " << sJSONObject << std::endl;
    rapidjson::Document d;
    CameraData retCamData;
    d.Parse(sJSONObject.c_str());
    rapidjson::Value& s = d["ID_BELL"];
	if(!s.IsNull())
    {
        //std::cout << "ID_BELL : " << s.GetString() << std::endl;
        retCamData.SetBellID(s.GetString());
    }
	s = d["ID_CAM"];
    if(!s.IsNull())
    {
        //std::cout << "ID_CAM : " << s.GetString() << std::endl;
        retCamData.SetCamID(s.GetString());
    }
	s = d["MAIN_URL"];
    if(!s.IsNull())
    {
        //std::cout << "MAIN_URL : " << s.GetString() << std::endl;
        retCamData.SetMainURL(s.GetString());
    }
	s = d["SUB_URL"];
    if(!s.IsNull())
    {
        //std::cout << "SUB_URL : " << s.GetString() << std::endl;
        retCamData.SetSubURL(s.GetString());
    }
    return retCamData;
}

std::string ClientAPI::CurlExecute(std::string url, std::string type, std::string data)
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer = "";
  //std::string url = NETSOFT_PUSH_IMAGE_URL;
  //std::string type = CONTENT_TYPE;
  //std::string data = "{\"id_Bell\":\"SS00122F5E0A202\", \"id_Cam\":\"1A2D3B4C5D6E\", \"image_Path\":\"http://221.132.23.2/img/1A2D3B4C5D6E/180117-194201.png\"}";
  curl = curl_easy_init();
  if(curl) {
    struct curl_slist *chunk = NULL;
    /* Remove a header curl would otherwise add by itself */ 
    chunk = curl_slist_append(chunk, type.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); std::cout << "[ClientAPI]URL: " << url << std::endl;
    //curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str()); std::cout << "[ClientAPI]Data: " << data << std::endl;
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)std::strlen(data.c_str()));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    readBuffer.erase(std::remove(readBuffer.begin(), readBuffer.end(), '\\'), readBuffer.end());
    //std::cout << readBuffer << std::endl;
  }
  return readBuffer;

}