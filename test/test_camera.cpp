#include "CameraHandler.h"
#include <iostream>

int main(){
    CameraHandler cameraHandler;
    CameraData* pCameraData = new CameraData();
    pCameraData->SetBellID("SS123456");
    pCameraData->SetCamID("Fa123FF456");
    pCameraData->SetMainURL("rtsp://admin:123456@113.161.61.89:42554/profile1");
    pCameraData->SetPath("test.png");
    int retcode = cameraHandler.CaptureImage(pCameraData);
    std::cout << "Ret code: " << retcode << std::endl;
}
