from Event import Event
from Event import ScriptNone

class ScriptTalk(Event):
    def __init__(self, syscall):
        Event.__init__(self, syscall)

    def Action(self):
        self.ShowMsg("Haha")


class ScriptPaper(Event):
    def __init__(self, syscall):
        Event.__init__(self, syscall)

    def Action(self):
        self.ShowImg(0, "pictures/paper1.png", (0.5, 0.5), (1, 1))
        self.Sleep(2000)
        self.KillImg(0)


class ScriptPaper2(Event):
    def __init__(self, syscall):
        Event.__init__(self, syscall)

    def Action(self):
        self.ShowImg(0, "pictures/paper2.png", (0.5, 0.5), (1, 1))
        self.Sleep(2000)
        self.KillImg(0)
