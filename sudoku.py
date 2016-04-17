# Sudoku number generation
# Prints random sudoku table
# Author Youngjin Kim  yachess@gmail.com

import random

# Group numbers 0..8 in which all number is unique remainder of 3
# This sequence is to be used as a sequence of appearance of a number in 
# a small 3x3 box. 

l=[[0,1,2],[3,4,5],[6,7,8]]

# Then suffle group and numbers in them
for i in range(10):
    r1=random.randint(0,2)
    r2=random.randint(0,2)
    l[r1],l[r2] = l[r2],l[r1]
for i in range(3):
    for j in range(10):
        r1=random.randint(0,2)
        r2=random.randint(0,2)
        l[i][r1],l[i][r2] = l[i][r2],l[i][r1]

# Flatten the list
l=(sum(l,[])) 

def print_board(board):
    for i,sq in enumerate(board):
        print(sq),
        if i%9==8:
            print("")

# Place numbers at the board in order of above indices
# relative to bounding box in vertical order.
board=[0 for _ in range(81)]

for n in range(1,10):
    for i,s in enumerate(l):
        # convert into global coordinates then to square
        x = i*3//9*3 + s%3
        y = i*3%9 + s//3
        sq = y*9+x
        board[sq]=n
    # rotate the sequence
    l=l[1:]+l[:1]

print_board(board)
