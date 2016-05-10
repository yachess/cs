import sys,random

board = [0 for _ in range(81)]

# Precalculate squares of each 9 3x3 box
bx_sqrs = [[0,1,2,9,10,11,18,19,20],
        [3,4,5,12,13,14,21,22,23],
        [6,7,8,15,16,17,24,25,26],
        [27,28,29,36,37,38,45,46,47],
        [30,31,32,39,40,41,48,49,50],
        [33,34,35,42,43,44,51,52,53],
        [54,55,56,63,64,65,72,73,74],
        [57,58,59,66,67,68,75,76,77],
        [60,61,62,69,70,71,78,79,80]]

def print_board(board):
    for i,v in enumerate(board):
        print(v),
        if i%9==8: print("")

def get_avail_sqrs(n,box):
    """ Yields available squares of a number in a given box """
    global board,constraints,bx_sqrs

    num_rows = [ i//9 for i,v in enumerate(board) if v==n ]
    num_cols = [ i%9 for i,v in enumerate(board) if v==n ]

    # Check if constraints square exists in box
    constraints_sq = -1
    for sq in bx_sqrs[box]:
        if constraints[sq]==n:
            constraints_sq = sq

    # Filter squares that don't overlap rows or columns with num sqrs
    if constraints_sq == -1:
        for sq in bx_sqrs[box]:
            if board[sq]!=0:
                continue
            if not (sq%9 in num_cols or sq//9 in num_rows) \
                and constraints[sq]==0:
                yield sq
    else:
        if not (constraints_sq%9 in num_cols \
                or constraints_sq//9 in num_rows):
            yield constraints_sq

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
    print(" Count of numbers must be 81")
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
