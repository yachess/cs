import Tkinter as tk

class Position(object):
    def __init__(self):
        self._d = [0 for _ in range(64)]
        pass
    def make(self,sq):
        pass
    def __repr__(self):
        s=""
        for i in range(64):
            s+=str(self._d[i])
        return s
pos = Position()
print(pos)

