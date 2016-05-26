# Game of life
# simple python example

import threading,time
import Tkinter as tk 

map_width = 200

# Cell status
none=0
dying=1
bearing=2
live=3

class App(tk.Frame):

    def __init__(self,master=None):
        tk.Frame.__init__(self,master)
        self.create_widgets()
        self.grid()
        self.rects = {}
        self.cells = {}
        self.running = False

    def create_widgets(self):
        self.canvas = tk.Canvas()
        self.canvas.grid()
        self.canvas.bind("<Button-1>",self.mouse_click)
        self.clear_btn = tk.Button(self,text="Clear", command = self.clear)
        self.run_btn = tk.Button(self,text="Start", command = self.run)
        self.quit_btn = tk.Button(self,text="Quit", command = self.quit)
        self.clear_btn.grid(row=1, column=0)
        self.quit_btn.grid(row=1, column=2)
        self.run_btn.grid(row=1, column=1)
        
    def mouse_click(self,event):
        x = event.x/6
        y = event.y/6
        key = y*map_width+x
        if key in self.rects:
            self.canvas.delete(self.rects[key])
            del self.rects[key]
            del self.cells[key]
        else:
            self.rects[key] = self.canvas.create_rectangle(
                    x*6, y*6, (x+1)*6, (y+1)*6, fill="black")
            self.cells[key] = live

    def clear(self):
        self.running = False
        self.canvas.delete("all")
        self.rects = {}
        self.cells = {}

    def run(self):
        self.running = not self.running
        if self.running:
            self.run_btn["text"]="Stop"
            self.step()
        else:
            self.run_btn["text"]="Start"

    def step(self):
        for key in range(map_width*map_width):
            if key in self.cells:
                if self.cells[key]==dying:
                    self.canvas.delete(self.rects[key])
                    del self.rects[key]
                    del self.cells[key]
                elif self.cells[key]==bearing:
                    x = key%map_width; y = key/map_width
                    self.rects[key]=self.canvas.create_rectangle(x*6,y*6,(x+1)*6,(y+1)*6,fill="black")
                    self.cells[key]=live

        for key in range(map_width*map_width):
            n_cnt = self.count_neighbors(key)
            if key in self.cells:
                if n_cnt is 2 or n_cnt is 3:
                    pass
                else:
                    self.cells[key] = dying
            elif n_cnt is 3:
                self.cells[key] = bearing

        if self.running:
            threading.Timer(0.5,self.step).start()

    def count_neighbors(self,key):
        x= key%map_width
        y= key/map_width
        c= 0
        neighbors = [
                key-map_width-1,key-map_width,key-map_width+1,
                key-1,key+1,
                key+map_width-1,key+map_width,key+map_width+1
        ]
        for n in neighbors:
            if n in self.cells and self.cells[n] is not bearing:
                c+=1
        return c

app = App()
app.master.title("PyLife")
app.mainloop()
