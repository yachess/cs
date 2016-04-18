import sys,random

board = [0 for _ in range(81)]
constraints=[ 0,0,8,0,0,4,0,9,0,
        0,0,0,0,8,1,0,5,4,
        0,2,0,0,0,0,0,0,1,
        2,0,7,0,5,0,0,0,0,
        8,3,0,0,1,0,0,0,0,
        0,4,0,0,9,7,0,0,0,
        0,0,0,0,0,0,0,0,6,
        0,6,0,0,0,3,0,4,0,
        7,0,5,0,0,0,0,0,0]
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

def get_available_squares(n,box):
# Returns available squares of n in a 3x3box
    global board, constraints,bx_sqs

    if box>8:
        return []
    sqs = []
    for sq in bx_sqs[box]:
#       if constraints[sq]==n:  # Solver code
#           return [sq]
        overlap = False 
        for i,v in enumerate(board):
            if v==n and (i%9==sq%9 or i//9==sq//9):
                overlap = True
        if board[sq]==0 and not overlap:
            sqs.append(sq)
    return sqs

def print_board(board):
    print("")
    for i,v in enumerate(board):
        print(v),
        if i%9==8: print("")

def fill(num,box):
# Recursively fill the squares in a box with given number
    global board
    if box>8:
        if num==9:    # Done
            return True
        else:           # fill next number
            num+=1
            box=0
#   print_board(board)
    found = False
    sqs = get_available_squares(num,box) 
    random.shuffle(sqs)
    for sq in sqs:
        board[sq] = num
        if fill(num,box+1):
            found = True
            return True
        else:
            board[sq] = 0
            

#if(len(sys.argv)==2)

board = [0 for _ in range(81)]

if fill(1,0):
    print_board(board)
    print("Success")
else:
    print("No Solution")
    

