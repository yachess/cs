import sys,random

board = [0 for _ in range(81)]

# Precalculate squares of each 9 3x3 box
bx_sqrs=[[0,1,2,9,10,11,18,19,20]]
bx_sqrs.append(map(lambda x: x+3, bx_sqrs[0]))
bx_sqrs.append(map(lambda x: x+6, bx_sqrs[0]))
bx_sqrs.append(map(lambda x: x+27, bx_sqrs[0]))
bx_sqrs.append(map(lambda x: x+27+3, bx_sqrs[0]))
bx_sqrs.append(map(lambda x: x+27+6, bx_sqrs[0]))
bx_sqrs.append(map(lambda x: x+54, bx_sqrs[0]))
bx_sqrs.append(map(lambda x: x+54+3, bx_sqrs[0]))
bx_sqrs.append(map(lambda x: x+54+6, bx_sqrs[0]))

def get_avail_sqrs(n,box):
    """ Yields available squares of a number in a given box """
    global board,constraints,bx_sqrs
    
    num_sqrs = []
    # Collect number squares
    pos = -1
    try:
        while 1:
            pos = board.index(n,pos+1)
            num_sqrs.append(pos)
    except ValueError:
        pass
    # Check if constraints square exists in box
    constraints_sq = -1
    for sq in bx_sqrs[box]:
        if constraints[sq]==n:
            constraints_sq = sq
    # Filter squares that doesn't overlap rows or columns with num sqrs
    if constraints_sq == -1:
        for sq in bx_sqrs[box]:
            if board[sq]!=0:
                continue
            conflict = False
            for nsq in num_sqrs:
                if sq%9 == nsq%9 or sq//9 == nsq//9:
                    conflict = True
                    break
            if not conflict and constraints[sq]==0:
                yield sq
    else:
        conflict = False
        for nsq in num_sqrs:
            if constraints_sq%9 == nsq%9 or constraints_sq//9 == nsq//9:
                conflict = True
                break
        if not conflict:
            yield constraints_sq

def print_board(board):
    for i,v in enumerate(board):
        print(v),
        if i%9==8: print("")

def fill(n,box):
    """ Recursively fill the squares in a box with given number """
    global board,num_try,freq_table
    if box==9:
        box=0
        n+=1
    if n==9:
        return True
    num=freq_table[n][0]
    num_try += 1
    gen= get_avail_sqrs(num,box)
    for sq in gen:
        board[sq] = num
        if fill(n,box+1):
            return True
        board[sq] = 0
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

num_try = 0
#freq_tableurence table to sort by frequency
freq_table = [[i,0] for i in xrange(1,10)]
for v in constraints:
    if v!= 0:
        freq_table[v-1][1]+=1
# Sort by second element in descending order
freq_table.sort(key=lambda x: x[1],reverse=True)

if fill(0,0):
    print("")
    print_board(board)
    print("Found solution in %d tries." % (num_try))
else:
    print("No Solution")
    

