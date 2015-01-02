#ifndef MSG_DEF
#define MSG_DEF

#include "WindowMsg.h"

namespace Msg{
    extern bool in_msg;
    extern bool can_end;
    extern WindowMsg* msg;
    
    void InitMsg();
    void StartMsg(const char* str_msg);
    void CloseMsg();
    bool IsMsgShow();
    bool IsMsgEnd();

};

#endif 
