from Event import Event 

class Event1(Event):
    def __init__(self, func):
        Event.__init__(self, func)
        self.config = {
            "event_name" : "event1",
            "image" : "hero.bmp",
            "trigger_condition" : "on chat",
            "solid" : "true", # TODO: change this to boolean
            "fixed_direction" : "false"
        }

    def Action(self):
        print("Enter Script's Action")
        self.global_value["Test1"] += 1
        self.global_flag["Test2"] = True
        self.ShowMsg("Hello~" + str(self.global_value["Test1"]))
        self.DoMove((["Right"],
                     ["Right"],
                     ["Right"]))
        self.WaitForMove()
        self.gameobject["object1"] = 1
        self.gameobject["object2"] = 2
        self.PlaySE("Swoosh.wav")
        self.PlayBGM("Under_Water.wav")
        print("ajksdhkash[[" + str(self.gameobject["object1"]) + "]]")
