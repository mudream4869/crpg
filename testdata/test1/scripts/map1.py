# coding=UTF-8

from Event import Event
from Event import MoveList

def myabs(a):
    if a < 0 :
        return -a
    else:
        return a

class TestChase(Event):
    def __init__(self, func):
        Event.__init__(self, func)
        self.AutoConfig()
        self.config["image"] = "hero.bmp"
        #self.config["chase_move"] = True
        self.config["trigger_condition"] = "sync"
    def Action(self):
        pass
        #dx = myabs(self.event_property.GetX() - self.hero_property.GetX())
        #dy = myabs(self.event_property.GetY() - self.hero_property.GetY())
        #if dx + dy <= 1:
        #    self.ShowMsg("You Died")

class TestAni(Event):
    def __init__(self, func):
        Event.__init__(self, func)
        self.AutoConfig()
        self.config["image"] = "hero.bmp"
        self.config["stay"] = True
        self.config["auto_move"] = (
            MoveList()
            .To(MoveList.DIR_UP)
            .Gen()
        )

class TestAutoMove(Event):
    def __init__(self, func):
        Event.__init__(self, func)
        self.AutoConfig()
        self.config["image"] = "hero.bmp"
        self.config["auto_move"] = (
            MoveList()
            .To(MoveList.DIR_LEFT)
            .To(MoveList.DIR_UP)
            .To(MoveList.DIR_RIGHT)
            .To(MoveList.DIR_DOWN)
            .Gen()
        )

    def Action(self):
        pass

class Event1(Event):
    def __init__(self, func):
        Event.__init__(self, func)
        self.AutoConfig()
        self.config["image"] = "hero.bmp"
        self.config["fixed_direction"] = False
        self.config["reject_cond"] = [
            ["flag", "Test2"]
        ]

    def Action(self):
        print("Enter Script's Action")
        self.global_value["Test1"] += 1
        self.ShowMsg(u"中文字測試haha\n換行")
        self.DoMove(
            MoveList()
            .To(MoveList.DIR_RIGHT, 3)
            .SetSpeed(1)
            .FaceTo(MoveList.DIR_UP)
            .Sleep(50)
            .Backward()
            .Toward()
            .Gen()
        )

        self.ShowImg(0, "pictures/haha.png", (1, 1), (1, 1))
        self.WaitForMove()
        self.KillImg(0) 
        self.gameobject["object2"] = 2
        self.gameobject["object1"] = 1
        self.PlaySE("Swoosh.wav")
        self.PlayBGM("Under_Water.wav")
        self.ShowSaveFile()

class EventTestAuto(Event):
    def __init__(self, func):
        Event.__init__(self, func)
        self.AutoConfig()
        self.config["trigger_condition"] = "sync"
        self.config["solid"] = False
        self.config["display_cond"] = [["flag", "Test2"]]

    def Action(self):
        self.gameobject["object1"] = 3
        self.global_flag["Test2"] = False
