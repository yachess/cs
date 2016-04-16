# Eight Queen puzzle using backtracking
# @ yachess@gmail.com Youngjin Kim

import sys
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
    for i in range(8):
        sq = row*8+i
        if can_place_queen_at(sq):
            queens.append(sq)
            if solve(row+1):
                found = True
            else:
                queens.pop()
    if not found:
        return False
    return True

def print_queens():
    b=0L
    for q in queens:
        b |= 1L<<q
    for i in range(64):
        s = ".Q" if b&1L<<i else ". "
        sys.stdout.write(s)
        if i%8==7: 
            sys.stdout.write("\n")

if solve(0):
    print_queens()
    print("Success")
else:
    print_queens()
    print("No Solution")
