#include "ClientAPI.h"

int main()
{
    ClientAPI testClientAPI;
    BellData testBellData;
    testClientAPI.GetCameraList(&testBellData);
    testBellData.GetCameraData(0).SetCamID("1A2D3B4C5D6E");
    testBellData.GetCameraData(0).SetPath("http://221.132.23.2/img/1A2D3B4C5D6E/180117-194201.png");
    testBellData.GetCameraData(1).SetCamID("1A2D3B4C5D6F");
    testBellData.GetCameraData(1).SetPath("http://221.132.23.2/img/1A2D3B4C5D6F/180117-194201.png");
    testClientAPI.PostImageInfo(&testBellData);
}