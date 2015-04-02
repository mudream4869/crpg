class Random:
    def __init__(self, seed = 2):
        self.a = 10000007
        self.b = 31
        self.salt = 0xdeadbeef
        self.x = seed

    def Rand(self):
        self.x = self.x*self.a + self.b
        self.x ^= self.salt;
        self.x %= 10000000000
        return self.x
