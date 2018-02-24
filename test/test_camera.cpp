#include "CameraHandler.h"
#include <iostream>

int main(){
    CameraHandler cameraHandler;
    CameraData* pCameraData = new CameraData();
    pCameraData->SetBellID("SS123456");
    pCameraData->SetCamID("Fa123FF456");
    pCameraData->SetMainURL("rtsp://10.4.1.231/axis-media/media.amp");
    pCameraData->SetPath("/home/bell/test.png");
    cameraHandler.SetCamdata(pCameraData);
    if(cameraHandler.CaptureImage()) std::cout << "ERR" << std::endl;
    else cameraHandler.SaveImage();
}
