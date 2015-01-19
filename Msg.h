#ifndef MSG_DEF
#define MSG_DEF

#include <condition_variable>
#include "WindowMsg.h"

namespace Msg{
    extern bool in_msg;
    extern bool can_end;
    extern WindowMsg* msg;
    
    std::condition_variable* GetMsgSignal();
    
    void InitMsg();
    void StartMsg(const char* str_msg);
    void CloseMsg();
    bool IsMsgShow();
    bool IsMsgEnd();

};

#endif 
