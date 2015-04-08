# coding=UTF-8

from Event import Event

class EventSavePoint(Event):
    def __init__(self, func):
        Event.__init__(self, func)
        self.AutoConfig() 
        self.config["event_name"] = "event_save_point"
        self.config["image"] = "sp.png"
        self.config["solid"] = False
        self.config["priority"] = 2

    def Action(self):
        self.ShowSaveFile()


class Main1(Event):
    def __init__(self, func):
        Event.__init__(self, func)
        self.AutoConfig()
        self.config["trigger_condition"] = "sync"
        self.config["solid"] = False
        self.config["reject_cond"] = [["flag", "main_ok"]]

    def Action(self):
        self.ShowMsg(u"請逃離這個房間。")
        self.global_flag["main_ok"] = True


class DoorEvent(Event):
    def __init__(self, func):
        Event.__init__(self, func)
        self.AutoConfig()
        self.config["image"] = "doortile.png"

    def Action(self):
        self.ShowMsg(u"請輸入密碼。")
        if self.ShowInputNumber() == 1403:
            self.ShowMsg(u"成功解鎖。")
            self.ReturnStart()
        else:
            self.ShowMsg(u"密碼錯誤。")


class TalkNo(Event):
    def __init__(self, func):
        Event.__init__(self, func)
        self.AutoConfig()
        self.config["priority"] = 2

    def Action(self):
        self.ShowMsg(u"找不到任何東西。")

class Talk1(TalkNo):
    def __init__(self, func):
        TalkNo.__init__(self, func)

class Talk3(TalkNo):
    def __init__(self, func):
        TalkNo.__init__(self, func)

class Talk4(TalkNo):
    def __init__(self, func):
        TalkNo.__init__(self, func)

class Talk2(Event):
    def __init__(self, func):
        Event.__init__(self, func)
        self.AutoConfig()
        self.config["priority"] = 2
        self.config["reject_cond"] = [["flag", "find_paper"]]

    def Action(self):
        self.ShowMsg(u"找到一張紙")
        self.gameobject["paper1"] = 1
        self.global_flag["find_paper"] = True

class Talk22(Event):
    def __init__(self, func):
        Event.__init__(self, func)
        self.AutoConfig()
        self.config["priority"] = 2
        self.config["display_cond"] = [["flag", "find_paper"]]

    def Action(self):
        self.ShowMsg(u"找不到任何東西")

class PainoPoint(Event):
    def __init__(self, func):
        Event.__init__(self, func)
        self.AutoConfig()
        self.config["priority"] = 2,
        self.config["display_cond"] = [["flag", "find_paper"]]
        self.config["reject_cond"] = [["flag", "find_paper2"]]

    def Action(self):
        self.ShowMsg(u"找到一張紙。")
        self.gameobject["paper2"] = 1
        self.global_flag["find_paper2"] = True


class Sleep(Event):
    def __init__(self, syscall):
        Event.__init__(self, syscall)
        self.AutoConfig()
        self.config["priority"] = 2

    def Action(self):
        self.ShowMsg(u"確定要睡覺？")
        if self.ShowMsgSelect([u"是", u"否"]) == 0 :
            self.GameOver()
