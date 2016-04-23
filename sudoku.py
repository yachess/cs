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

def get_available_squares(n,box):
# Returns available squares of n in a 3x3box
    global board, constraints,bx_sqs

    if box>8:
        return []
    sqs = []

    for sq in bx_sqs[box]:
        overlap = False 
        for i,v in enumerate(board):
            if v==n and i != sq and (i%9==sq%9 or i//9==sq//9):
                overlap = True
        if board[sq]==0 and not overlap:
            sqs.append(sq)

    return sqs

def print_board(board):
    for i,v in enumerate(board):
        print(v),
        if i%9==8: print("")

def fill(num,box):
# Recursively fill the squares in a box with given number
    global board
    if box>8:
        if num==9:      # Done
            return True
        else:           # handle next
            num+=1
            box=0
#   print("n:%d,box:%d" % (num,box))
#   print_board(board)

    sqs = get_available_squares(num,box) 
    random.shuffle(sqs)
    for sq in sqs:
        board[sq] = num
        if fill(num,box+1):
            return True
        else:
            board[sq] = 0
    return False
            
#if(len(sys.argv)==2)

board = [0 for _ in range(81)]

if fill(1,0):
    print_board(board)
    print("Success")
else:
    print("No Solution")
    

