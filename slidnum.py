import Tkinter as tk
import random

up = 0
down = 1
left = 2
right = 3

class Board(object):
    def __init__(self):
        self.nums = [1,2,3,4,5,6,7,8,9,0]
        self.sorted = self.nums[:]
    def shuffle(self):
        for i in range(1,10):
            rn1 = random.randint(0,9)
            rn2 = random.randint(0,9)
            self.nums[rn1], self.nums[rn2] = self.nums[rn2], self.nums[rn1] 
    def solve():
        pass
    def __str__(self):
        return self.nums.__str__()
    def is_sorted(self):
        return self.nums == self.sorted
    def make(self,dir):
        zerosq = self.num.index(0);
        zx = zerosq % 3
        zy = zerosq // 3
        pass    
    def eval(self):
        retval=0
        for i in range(1,10):
            if self.nums[i]==self.sorted[i]:
                retval+=1
        return retval
board = Board()
print(board.is_sorted())
board.shuffle()
print(board)
print(board.is_sorted())
