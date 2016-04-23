import sys
import Tkinter as tk


def build_rays():
    rays=[]
    for sq in range(64):
        rays.append([[x for x in range(sq+1,64,1) if x//8==sq//8],
            [x for x in range(sq+9,64,9) if x//8>sq//8 and x%8>sq%8],
            [x for x in range(sq+8,64,8)],
            [x for x in range(sq+7,64,7) if x//8>sq//8 and x%8<sq%8],
            [x for x in range(sq-1,-1,-1) if x//8==sq//8],
            [x for x in range(sq-9,-1,-9) if x//8<sq//8 and x%8<sq%8],
            [x for x in range(sq-8,-1,-8)],
            [x for x in range(sq-7,-1,-7) if x//8<sq//8 and x%8>sq%8]])
    return rays            

def print_rays(rays,sq):
    b = 0L
    for i in range(8):
        for j in rays[sq][i]:
            b |= 1L << j
    for sq in range(64):
        s=".X" if b&1<<sq else "._"
        sys.stdout.write(s)
        if sq%8==7:
            sys.stdout.write("\n")

class Position(object):
    def __init__(self):
        self._d = [0 for _ in range(64)]
        self.bb = [0L,0L]
        self.t = 0
        pass
    def flip(self,sq):
        for i in range(8):
            cnt=0
            for idx,dsq in enumerate(rays[sq][i]):
                if self.bb[self.t^1]&1<<dsq:
                    cnt+=1
                else:
                    break
            if cnt>0 and idx<8 and self.bb[self.t]&1<<rays[sq][i][idx]:
                for j in range(0,idx):
                    self.bb[self.t]^=1<<rays[sq][i][j]
                    self.bb[self.t^1]^=1<<rays[sq][i][j]
        if self.on_flip != None:
            self.on_flip(self.t,sq) 
    def make(self,sq):
        self.bb[self.t] ^=1<<sq
        if self.on_make != None:
            self.on_make(self.t,sq) 
        self.flip(sq)
        self.t^=1
        pass
    def make_if_legal(self,sq):
        if self.legal(sq):
            self.make(sq)
    def legal(self,sq):
        empty = ~(self.bb[self.t] | self.bb[self.t^1])
        if empty &1<<sq:
            return True

    def __repr__(self):
        s=""
        for sq in range(64):
            s+= ".X" if self.bb[0]&1<<sq else (".O" if self.bb[1]&1<<sq else "._")
            if sq%8==7: s+="\n"
        return s

class OthelloFrame(tk.Frame):
    def __init__(self,parent):
        tk.Frame.__init__(self,parent)
        self.parent = parent
        self.objs = [ None for _ in range(64)]

        self.initUI()
     
    def initUI(self):
        self.parent.title("Othello")
        self.canvas = tk.Canvas(self,width=8*40,height=8*40)
        self.quitBtn = tk.Button(text="Quit",command=self.quit)
        self.canvas.bind("<Button-1>",self.click)
        self.canvas.pack()
        self.quitBtn.pack()
        self.pack()


    def create_disk(self,sq,color):
        self.objs[sq]=self.canvas.create_oval((sq%8)*40,(sq//8)*40,(sq%8)*40+40,(sq//8)*40+40,fill=color)
    
    def remove_disk(self,sq):
        self.canvas.delete(self.objs[sq])
        self.objs[sq]=None

    def click(self,event):
        sq = event.y/40*8+event.x/40
        if self.select_cell != None:
            self.select_cell(sq)
        
    def handle_make(self,color,sq):
        if color==0:
            self.create_disk(sq,"Black")
        else:
            self.create_disk(sq,"White")
    def handle_flip(self,color,sq):
        self.remove_disk(sq)
        if color==0:
            self.create_disk(sq,"Black")
        else:
            self.create_disk(sq,"White")

rays = build_rays()
pos = Position()

for i in range(64):
    print_rays(rays,i)
print(pos)

f = OthelloFrame(tk.Tk())
pos.on_make = f.handle_make
pos.on_flip = f.handle_flip
f.select_cell = pos.make_if_legal

pos.make(28)
pos.make(27)
pos.make(35)
pos.make(36)

f.mainloop()
