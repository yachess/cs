import Tkinter as tk
from random import randrange, shuffle
import time,threading

class App(tk.Frame):

    def __init__(self,master=None):
        tk.Frame.__init__(self, master)
        self.create_widgets()
        self.grid()
        self.w = 24
        self.h = 30
        self.visited = [[0] * self.w +[1] for _ in range (self.h)] + \
                [[1]*(self.w+1)]
        self.walk(randrange(self.w),randrange(self.h))
        self.pack()

    def create_widgets(self):
        self.canvas = tk.Canvas(self) 
        self.new_btn = tk.Button(self, text = "New", command = self.new)
        self.quit_btn = tk.Button(self, text = "Quit", command = self.quit)
        self.canvas.grid(row=0, column=0)
        self.new_btn.grid(row=1, column=0)
        self.quit_btn.grid(row=1, column=1)

    def new(self):
        self.canvas.delete("all")
        self.visited = [[0] * self.w +[1] for _ in range (self.h)] + \
                [[1]*(self.w+1)]
        self.walk(randrange(self.w),randrange(self.h))
        pass
    
    def walk(self,x,y):
        self.x=x; self.y=y
#       print "{0},{1}".format(x,y)
        try:
            self.visited[x][y]=1
        except IndexError as e:
            print "visited idx:{0},{1}".format(x,y)
        d = [(x,y-1),(x-1,y),(x+1,y),(x,y+1)]
        shuffle(d)
        for (xx,yy) in d:
            if not self.visited[xx][yy]:
                self.canvas.create_line(
                        x*10+10, y*10+10,
                        xx*10+10,yy*10+10,
                        width=8, capstyle='projecting'
                )
                self.walk(xx,yy) 

app = App()
app.master.title("Maze Test")
app.mainloop()
