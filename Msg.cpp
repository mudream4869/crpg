#include "Msg.h"
#include "WindowMsg.h"

bool Msg::in_msg;
bool Msg::can_end;
WindowBlockType* Msg::msg;

/*std::condition_variable* Msg::GetMsgSignal(){
    return msg->GetSignal();
}*/

void Msg::InitMsg(){
    in_msg = false;
    can_end = false;
    msg = nullptr;
    return;
}

void Msg::StartMsg(const char* str_msg){
    msg = new WindowMsg(str_msg);
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
