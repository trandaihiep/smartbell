/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
This file contain camera data and provide data access methods

*Contributors:
   Pham Chi Viet Hung:	01-Feb-2018: Initial implementation and documentation.
*****************************************/
///****************  INCLUDE ***************///
#include "CameraData.h"
#include <iostream>
/*
 * Class: CameraData
///************** FUCNTION **************///
// Description: Contructor
// Parameters: 
//
// Return: None
CameraData::CameraData(){
  
}
///************** FUCNTION **************///
// Description: Decontructor
// Parameters: 
//
// Return: None
CameraData::~CameraData(){
}

// Description: 
// Parameters: 
//
// Return: None
std::string CameraData::GetBellID(){
  return m_sBellID;
}
// Description: 
// Parameters: 
//
// Return: None
void CameraData::SetBellID(std::string sBellID){
  m_sBellID = sBellID;
}
// Description: 
// Parameters: 
//
// Return: None
std::string CameraData::GetCamID(){
  return m_sCamID;
}
// Description: 
// Parameters: 
//
// Return: None
void CameraData::SetCamID(std::string sCamID){
  m_sCamID=sCamID;
}
// Description: 
// Parameters: 
//
// Return: None
std::string CameraData::GetMainURL(){
  return m_sMainURL;
}
// Description: 
// Parameters: 
//
// Return: None
void CameraData::SetMainURL(std::string sMainURL){
  m_sMainURL = sMainURL;
}
// Description: 
// Parameters: 
//
// Return: None
std::string CameraData::GetSubURL(){
  return m_sSubURL;
}
// Description: 
// Parameters: 
//
// Return: None
void CameraData::SetSubURL(std::string sSubURL){
  m_sSubURL = sSubURL;
}
// Description: 
// Parameters: 
//
// Return: None
std::string CameraData::GetPath(){
  return m_sPath;
}
// Description: 
// Parameters: 
//
// Return: None
void CameraData::SetPath(std::string sPath){
  m_sPath = sPath;
}
// Description: 
// Parameters: 
//
// Return: None
cv::Mat CameraData::GetImage(){
  return m_mImage;
}
// Description: 
// Parameters: 
//
// Return: None
void CameraData::SetImage(cv::Mat dImage){
  m_mImage = dImage;
}