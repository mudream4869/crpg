#include "Msg.h"

bool Msg::in_msg;
bool Msg::can_end;
WindowMsg* Msg::msg;

void Msg::InitMsg(){
    in_msg = false;
    can_end = false;
    msg = nullptr;
    return;
}

void Msg::StartMsg(const char* str_msg){
    msg = new WindowMsg(0.1, 1.5, 1.8, 0.4, str_msg);
    in_msg = true;
    return;
}

void Msg::CloseMsg(){
    if(msg != nullptr)
        delete msg;
    in_msg = false;
    return;
}

bool Msg::IsMsgShow(){
    return in_msg;
}

bool Msg::IsMsgEnd(){
    return msg->IsOk();
}
