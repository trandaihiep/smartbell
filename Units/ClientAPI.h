/*****************************************
Copyright (c) 2018 VNPT-Technology
All rights reserved. This program and the accompanying materials
are made available under the terms of GNU GPL v3 which accompany this distribution.

* Description:
Quản lý thao tác của camera

*Contributors:
   Pham Chi Viet Hung:	08-Feb-2018: Initial implementation and documentation.
*****************************************/
#ifndef CLIENT_API_H_
#define CLIENT_API_H_
///****************  INCLUDE ***************///
#include "BellData.h"

///****************  DEFINE ****************///


///**************  NAMESPACE **************///

/*
 * Class: ClientAPI
 *
 *  Handle connect IP camera tasks
 */
class ClientAPI{

   private: 
        ///*************** FUCNTION **************///

        ///*************** VARIABLE **************///

   public:
        ///*************** FUCNTION **************///
        ClientAPI();
        virtual ~ClientAPI();
        int GetCameraList(BellData* pBellData);
        int PostImageInfo(BellData* pBellData);
        ///*************** VARIABLE **************///


};
#endif  // ClientAPI