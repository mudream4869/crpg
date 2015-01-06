from Event import Event

class ScriptNone(Event):
    def __init__(self, syscall):
        Event.__init__(self, syscall)
