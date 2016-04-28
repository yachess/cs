import threading,time,math
import Tkinter as tk


def koch(a,b):
    dst = math.sqrt(math.pow(b[0]-a[0],2) + math.pow(b[1]-a[1],2))
    pts = []
    # convert two point into angle
    dy = b[1] - a[1]
    dx = b[0] - a[0]
    rad = math.atan2(dy,dx)
    nx0 = a[0] + math.cos(rad)*dst/3
    ny0 = a[1] + math.sin(rad)*dst/3
    
    # Now turn -60 degree (radian: rad+60/360 * 2 * pi)
    rad = rad-(1.0/6)*2*math.pi
    nx1 = nx0+math.cos(rad)*dst/3
    ny1 = ny0+math.sin(rad)*dst/3
    
    # turn +120 deg.
    rad = rad+(1.0/3)*2*math.pi
    nx2 = nx1+math.cos(rad)*dst/3
    ny2 = ny1+math.sin(rad)*dst/3

    return [(a[0],a[1]),(nx0,ny0),(nx1,ny1),(nx2,ny2),(b[0],b[1])]

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

n = 0
def step():
    global n,f
    
    l=[]
    l.append((50,150))
    l.append((550,150))
    l.append((300,580))
    l.append((50,150))

    for i in range(n):
        l = kochrize(l)
    f.remove_all()
    old_pt = None
    for pt in l:
        if old_pt != None:
            f.add_line(old_pt, pt)
        old_pt = pt
    n = (n+1)%6
    threading.Timer(3.0,step).start()

def kochrize(ls):
    new_l = []
    old_pt = None
    for pt in ls:
        if old_pt != None:
            new_l += koch(old_pt,pt)
        old_pt = pt
    return new_l

f = KochFrame(tk.Tk())
step()
f.mainloop()
