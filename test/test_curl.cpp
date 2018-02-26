#include "ClientAPI.h"

int main()
{
    ClientAPI testClientAPI;
    BellData testBellData;
    bool retBool = testBellData.ParseBellData("$SS00122F5E0A202,59,1#");
    testClientAPI.GetCameraList(&testBellData);
    //.SetPath("http://221.132.23.2/img/1A2D3B4C5D6E/180117-194201.png");
    //SetPath("http://221.132.23.2/img/1A2D3B4C5D6F/180117-194201.png");
    testClientAPI.PostImageInfo(&testBellData);
}