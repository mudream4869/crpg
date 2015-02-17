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


class MoveList:
    DIR_LEFT = 1
    DIR_RIGHT = 2
    DIR_UP = 3
    DIR_DOWN = 0
    DIR_NONE = -1
    
    CMD_TO = 0;
    CMD_TOWARD = 1;
    CMD_BACKWARD = 2;
    CMD_FACETO = 3;
    CMD_SLEEP = 4;
     
    def __init__(self):
        self.mmlist = []

    def To(self, direction = DIR_NONE, step = 1):
        self.mmlist.append([MoveList.CMD_TO, direction, step])
        return self
    
    def Toward(self, step = 1):
        self.mmlist.append([MoveList.CMD_TOWARD, step])
        return self

    def Backward(self, step = 1):
        self.mmlist.append([MoveList.CMD_BACKWARD, step])
        return self
    
    def FaceTo(self, direction = DIR_NONE):
        print(1, direction)
        self.mmlist.append([MoveList.CMD_FACETO, direction])
        return self
    
    def Sleep(self, ms = 1000):
        self.mmlist.append([MoveList.CMD_SLEEP, ms])
        return self

    def Gen(self):
        print("Gen!!!")
        ret_arr = []
        for item in self.mmlist:
            if(item[0] == MoveList.CMD_TO):
                for _step in range(0, item[2]):
                    ret_arr.append([item[0], item[1]])
            elif(item[0] == MoveList.CMD_TOWARD):
                for _step in range(0, item[1]):
                    ret_arr.append([item[0], 0])
            elif(item[0] == MoveList.CMD_BACKWARD):
                for _step in range(0, item[1]):
                    ret_arr.append([item[0], 0])
            elif(item[0] == MoveList.CMD_FACETO):
                ret_arr.append([item[0], item[1]])
            elif(item[0] == MoveList.CMD_SLEEP):
                ret_arr.append([item[0], item[1]])
        return ret_arr


class Event:
    rand_seq = None
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
            "reject_cond" : [],
            "stay" : False,
            "auto_move" : []
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
        self.syscall("DoMove", self.config["event_name"], arr)
    
    def HeroMove(self, arr):
        self.syscall("HeroMove", arr)
    
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
