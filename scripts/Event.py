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
    def __init__(self, syscall):
        self.syscall = syscall
        self.global_value = GlobalValue(syscall)
        self.global_flag = GlobalFlag(syscall)
        self.gameobject = GameObject(syscall)

    def ShowMsg(self, msg):
        self.syscall("ShowMsg", msg)
    
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
    
    def WaitForMove(self):
        self.syscall("WaitForMove", self.config["event_name"])

    def ChangeMap(self, map_name, point, direction = -1):
        self.syscall("ChangeMap", map_name, point[0], point[1], direction)

    def PlaySE(self, se_name):
        self.syscall("PlaySE", se_name)

    def PlayBGM(self, bgm_name):
        self.syscall("PlayBGM", bgm_name)
 
    def Action(self):
        return
