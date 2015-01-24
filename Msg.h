#ifndef MSG_DEF
#define MSG_DEF

#include "WindowBlockType.h"

namespace Msg{
    extern bool in_msg;
    extern bool can_end;
    extern WindowBlockType* msg;
    
    //std::condition_variable* GetMsgSignal();
    
    void InitMsg();
    void StartMsg(const char* str_msg);
    void CloseMsg();
    bool IsMsgShow();
    bool IsMsgEnd();

};

#endif 
