from Tool import Random

class GlobalValue:
    def __init__(self, syscall):
        self.syscall = syscall

    def __setitem__(self, key, item):
        vitem = int(item)
        self.syscall("SetValue", key, vitem)
    
    def __getitem__(self, key):
        return self.syscall("GetValue", key)


class GlobalFlag:
    def __init__(self, syscall):
        self.syscall = syscall

    def __setitem__(self, key, item):
        self.syscall("SetFlag", key, item)

    def __getitem__(self, key):
        return self.syscall("GetFlag", key);


class GameObject:
    def __init__(self, syscall):
        self.syscall = syscall

    def __setitem__(self, key, item):
        vitem = int(item)
        self.syscall("SetGameObject", key, item)

    def __getitem__(self, key):
        return self.syscall("GetGameObject", key)


class Event:
    rand_seq = None
    DIR_LEFT = 1
    DIR_RIGHT = 2
    DIR_UP = 3
    DIR_DOWN = 0
    def __init__(self, syscall):
        self.syscall = syscall
        self.global_value = GlobalValue(syscall)
        self.global_flag = GlobalFlag(syscall)
        self.gameobject = GameObject(syscall)
        
        if Event.rand_seq == None:
            Event.rand_seq = Random()

    def AutoConfig(self):
        rand_name = "__" + str(Event.rand_seq.Rand())
        self.config = {
            "event_name" : rand_name,
            "image" : "",
            "trigger_condition" : "on chat",
            "solid" : True,
            "fixed_direction" : True,
            "priority" : 1,
            "display_cond" : [],
            "reject_cond" : []
        }
    
    def ShowMsg(self, msg):
        self.syscall("ShowMsg", str(msg))
    
    def ShowInputNumber(self):
        return self.syscall("ShowInputNumber")
    
    def ShowMsgSelect(self, arr):
        return self.syscall("ShowMsgSelect", arr)

    def ShowSaveFile(self):
        self.syscall("ShowSaveFile")

    def DoMove(self, arr):
        to_arr = []
        for item in arr:
            if item[0] == "Up": to_arr.append(3)
            if item[0] == "Down" : to_arr.append(0)
            if item[0] == "Left": to_arr.append(1)
            if item[0] == "Right" : to_arr.append(2)
        self.syscall("DoMove", self.config["event_name"], to_arr)
    
    def HeroMove(self, arr):
        to_arr = []
        for item in arr:
            if item[0] == "Up": to_arr.append(3)
            if item[0] == "Down" : to_arr.append(0)
            if item[0] == "Left": to_arr.append(1)
            if item[0] == "Right" : to_arr.append(2)
        self.syscall("HeroMove", to_arr)
    
    def WaitForMove(self):
        self.syscall("WaitForMove", self.config["event_name"])
    
    def WaitForHeroMove(self):
        self.syscall("WaitForHeroMove")

    def ChangeMap(self, map_name, point, direction = -1):
        self.syscall("ChangeMap", map_name, point[0], point[1], direction)

    def PlaySE(self, se_name):
        self.syscall("PlaySE", se_name)

    def PlayBGM(self, bgm_name):
        self.syscall("PlayBGM", bgm_name)
    
    def SetMask(self, start_color, end_color, ms):
        self.syscall("SetMask", start_color, end_color, ms)
    
    def Sleep(self, ms):
        self.syscall("Sleep", ms)

    def ShowImg(self, index, img_name, pos, rect):
        self.syscall("ShowImg", index, img_name, pos, rect)

    def KillImg(self, index):
        self.syscall("KillImg", index)
    
    def GameOver(self):
        self.syscall("GameOver")

    def ReturnStart(self):
        self.syscall("ReturnStart")

    def Action(self):
        return

 
class ScriptNone(Event):
    def __init__(self, syscall):
        Event.__init__(self, syscall)
