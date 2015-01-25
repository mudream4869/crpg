from Event import Event 

class Event1(Event):
    def __init__(self, func):
        Event.__init__(self, func)
        self.config = {
            "event_name" : "event1",
            "image" : "hero.bmp",
            "trigger_condition" : "on chat",
            "solid" : True,
            "fixed_direction" : False,
            "priority" : 1,
            "display_cond" : [],
            "reject_cond" : [
                ["flag", "Test2"]
            ],
        }

    def Action(self):
        print("Enter Script's Action")
        self.global_value["Test1"] += 1
        self.global_flag["Test2"] = True
        self.ShowMsg("Hello~" + str(self.global_value["Test1"]))
        self.DoMove((["Right"],
                     ["Right"],
                     ["Right"],
                     ["Down"]))
        self.ShowImg(0, "pictures/haha.png", (1, 1), (1, 1))
        self.WaitForMove()
        self.KillImg(0) 
        self.gameobject["object2"] = 2
        self.PlaySE("Swoosh.wav")
        self.PlayBGM("Under_Water.wav")
        self.ShowMsg(self.ShowInputNumber())

class EventTestAuto(Event):
    def __init__(self, func):
        Event.__init__(self, func)
        self.config = {
            "event_name" : "event2",
            "image" : "",
            "trigger_condition" : "sync",
            "solid" : False,
            "fixed_direction" : False,
            "priority" : 1,
            "display_cond" : [
                ["flag", "Test2"],
            ],
            "reject_cond" : []
        }

    def Action(self):
        self.gameobject["object1"] = 3
        self.global_flag["Test2"] = False
