import threading,time,math
import Tkinter as tk


def mid_pt(a,b):
    dst = math.sqrt(math.pow(b[0]-a[0],2) + math.pow(b[1]-a[1],2))
    # convert two point into angle
    dy = b[1] - a[1]
    dx = b[0] - a[0]
    rad = math.atan2(dy,dx)
    nx0 = a[0] + math.cos(rad)*dst/2
    ny0 = a[1] + math.sin(rad)*dst/2
    return (nx0,ny0)


def arrow(a,b,n,idx):
    dst = math.sqrt(math.pow(b[0]-a[0],2) + math.pow(b[1]-a[1],2))
    pts = []
    # convert two point into angle
    dy = b[1] - a[1]
    dx = b[0] - a[0]
    rad = math.atan2(dy,dx)
     
    dir = 1 if (n+idx)%2==0  else -1
    # Now turn 60 degree (radian: rad+60/360 * 2 * pi)
    rad += (1.0/6)*2*math.pi*dir
    nx0 = a[0]+math.cos(rad)*dst/2
    ny0 = a[1]+math.sin(rad)*dst/2
    
    rad -= (1.0/6)*2*math.pi*dir
    nx1 = nx0+math.cos(rad)*dst/2
    ny1 = ny0+math.sin(rad)*dst/2

    return [(a[0],a[1]),(nx0,ny0),(nx1,ny1),(b[0],b[1])]

class KochFrame(tk.Frame):
    def __init__(self, parent):
        tk.Frame.__init__(self, parent)
        self.parent = parent
        self.objs = []
        self.initUI()

    def initUI(self):
        self.parent.title("Koch Snowflake")
        self.canvas = tk.Canvas(self,width = 600, height = 600)
#       self.quitBtn = tk.Button(text="Quit", command = self.quit)
        self.canvas.pack()
#       self.quitBtn.pack()
        self.pack()

    def add_line(self,a,b):
        self.objs.append(self.canvas.create_line(a[0],a[1],b[0],b[1]))
    
    def remove_all(self):
        try:
            for o in self.objs:
                self.canvas.delete(o)
            self.objs = []
        except Exception:
            pass

def arrowrize(ls,n):
    global dir
    new_l = []
    old_pt = None
    cnt  = 0
    for i,pt in enumerate(ls):
        if old_pt != None:
            if (old_pt == pt):
                continue
            new_l += arrow(old_pt,pt,n,cnt)
            cnt += 1
        old_pt = pt
    return new_l

n = 0
def step():
    global n,f
    
    l=[]
    l.append((550,450))
    l.append((50,450))

    for i in range(n):
        l = arrowrize(l,i)
    f.remove_all()
    old_pt = None
    for pt in l:
        if old_pt != None:
            f.add_line(old_pt, pt)
        old_pt = pt
    n = (n+1)%9
    threading.Timer(3.0,step).start()


f = KochFrame(tk.Tk())
step()
f.mainloop()
