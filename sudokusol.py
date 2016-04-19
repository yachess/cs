import sys,random

board = [0 for _ in range(81)]
# precalculate squares of each 9 3x3 box
bx_sqs = []
bx_sqs.append([0,1,2,9,10,11,18,19,20])
bx_sqs.append(map(lambda x: x+3, bx_sqs[0]))
bx_sqs.append(map(lambda x: x+6, bx_sqs[0]))
bx_sqs.append(map(lambda x: x+27, bx_sqs[0]))
bx_sqs.append(map(lambda x: x+27+3, bx_sqs[0]))
bx_sqs.append(map(lambda x: x+27+6, bx_sqs[0]))
bx_sqs.append(map(lambda x: x+54, bx_sqs[0]))
bx_sqs.append(map(lambda x: x+54+3, bx_sqs[0]))
bx_sqs.append(map(lambda x: x+54+6, bx_sqs[0]))

def get_avail_sqrs(n,box):
# Returns available squares of n in a 3x3box
    global board, constraints,bx_sqs

    if box>8:
        return []
    sqs = []

    constraints_sq = -1
    for sq in bx_sqs[box]:
        if constraints[sq]==n:
            constraints_sq = sq
    
    for sq in bx_sqs[box]:
        overlap = False 
        for i,v in enumerate(board):
            if v==n and i != sq and (i%9==sq%9 or i//9==sq//9):
                overlap = True
        if board[sq]==0 and (constraints[sq]==0 or constraints[sq]==n) and not overlap:
            sqs.append(sq)
    if constraints_sq != -1:
        if constraints_sq in sqs:
            return [constraints_sq]
        else:
            return []

    return sqs

def print_board(board):
    for i,v in enumerate(board):
        print(v),
        if i%9==8: print("")

num_try = 0
def fill(num):
# Recursively fill the squares in a box with given number
    global board,num_try
    
    if num==10:      # Done
        return True
    num_try += 1
    result=False
    for sq0 in get_avail_sqrs(num,0):
        board[sq0] = num
        for sq1 in get_avail_sqrs(num,1):
            board[sq1] = num
            for sq2 in get_avail_sqrs(num,2):
                board[sq2] = num
                for sq3 in get_avail_sqrs(num,3):
                    board[sq3] = num
                    for sq4 in get_avail_sqrs(num,4):
                        board[sq4] = num
                        for sq5 in get_avail_sqrs(num,5):
                            board[sq5] = num
                            for sq6 in get_avail_sqrs(num,6):
                                board[sq6] = num
                                for sq7 in get_avail_sqrs(num,7):
                                    board[sq7] = num
                                    for sq8 in get_avail_sqrs(num,8):
                                        board[sq8] = num
                                        result = fill(num+1)
                                        if result:
                                            return True
                                        board[sq8] = 0
                                    board[sq7] = 0
                                board[sq6] = 0
                            board[sq5] = 0
                        board[sq4] = 0
                    board[sq3] = 0
                board[sq2] = 0
            board[sq1] = 0
        board[sq0] = 0
    return False

if len(sys.argv)!=2:
    print("Usage:python sudokusol.py [number sequence]")
    print("  use 0 for blank square")
    quit()

constraints=[]
for c in sys.argv[1]:
    constraints.append(int(c))

if len(constraints)!= 81:
    print(" count of numbers must be 81")
    quit()

if fill(1):
    print("")
    print_board(board)
    print("Found solution after %d trial." % (num_try))
else:
    print("No Solution")
    

