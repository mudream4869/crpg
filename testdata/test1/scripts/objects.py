from Event import Event
from Event import ScriptNone

class ScriptTalk(Event):
    def __init__(self, syscall):
        Event.__init__(self, syscall)

    def Action(self):
        self.ShowMsg("Haha")
