import random

inums = [x for x in xrange(16)]
nums = inums[:]
visited = []
def print_nums(nums):
    for i,n in enumerate(nums):
        print("%2d" % (n+1 if n != 15 else 00)),
        if i%4==3:
            print("")
    print("")

def pos_visited(nums,sq):
    global visited
    vi = False
    last_sq = nums.index(15)
    nums[sq],nums[last_sq] = nums[last_sq],nums[sq]
    if nums in visited:
        vi = True
    nums[sq],nums[last_sq] = nums[last_sq],nums[sq]
    return vi

def get_avail_sqrs(sq):
    global nums
    l=[]
    if (sq+1)%4!=0:
        if not pos_visited(nums,sq+1):
            l.append(sq+1)
    if (sq+4)//4<4:
        if not pos_visited(nums,sq+4):
            l.append(sq+4)
    if (sq-1)%4!=3:
        if not pos_visited(nums,sq-1):
            l.append(sq-1)
    if (sq-4)//4>=0:
        if not pos_visited(nums,sq-4):
            l.append(sq-4)
    return l

def match_num(nums):
    global inums
    cnt =0
    for i,n in enumerate(nums):
        if inums[i]==n:
            cnt+=1
    return cnt

def solve(m,match_cnt):
    global nums,inums,visited
    matches = match_num(nums)
#   print("matches:%d - %d" % (matches,m))
    if matches >= 10:
        return True
    if m>25:
        return False
    visited.append(nums[:])
#   elif matches > match_cnt:
#       m=0
#       return True
#   elif m > 25:
#       m=0
#       return False
    last_sq = nums.index(15)
#   print_nums(nums)
    sqs = get_avail_sqrs(last_sq)
#   print(sqs)
    for sq in sqs:
        nums[sq],nums[last_sq] = nums[last_sq],nums[sq]
        if solve(m+1,match_cnt):
            return True
        else:
            nums[sq],nums[last_sq] = nums[last_sq],nums[sq]
    return False 

random.shuffle(nums)
if solve(0,0):
    print(inums)
    print(nums)
    print("Success")
else:
    print("Fail")
