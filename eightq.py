# Eight Queen puzzle solver using backtracking
# Prints random eight queen position
# Author: Youngjin Kim yachess@gmail.com 

import sys
import random

queens = []

def can_place_queen_at(sq):
    global queens
    for q in queens:
        if q%8==sq%8 or q//8==sq//8 or \
            abs(q//8-sq//8) == abs(q%8-sq%8):
            return False
    return True

def solve(row):
    global queens
    if row==8:
        return True
    found = False
   
    l = range(8)
    random.shuffle(l)
    for i in l:
        sq = row*8+i
        if can_place_queen_at(sq):
            queens.append(sq)
            if solve(row+1):
                found = True
            else:
                queens.pop()
    if found:
        return True
    return False

def print_queens():
    for i in xrange(64):
        sys.stdout.write(".Q" if i in queens else ". ")
        if i%8==7: 
            sys.stdout.write("\n")

if solve(0):
    print_queens()
    print("Success")
else:
    print_queens()
    print("No Solution")
