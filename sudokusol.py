import sys,random

board = [0 for _ in range(81)]

# precalculate squares of each 9 3x3 box
bx_sqs=[[0,1,2,9,10,11,18,19,20]]
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

def fill(n,box):
# Recursively fill the squares in a box with given number
    global board,num_try,occ
    
    if box==9:
        box=0
        n+=1
    if n==9:
        return True
    num=occ[n][0]
    num_try += 1
    result=False
    for sq in get_avail_sqrs(num,box):
        board[sq] = num
        result = fill(n,box+1)
        if result:
            return True
        else:
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
#occurence table to sort by frequency
occ = [[i,0] for i in xrange(1,10)]
for v in constraints:
    if v!= 0:
        occ[v-1][1]+=1
# Sort by second element
occ.sort(key=lambda x: -x[1])

print(occ)
if fill(0,0):
    print("")
    print_board(board)
    print("Found solution after %d trial." % (num_try))
else:
    print("No Solution")
    

