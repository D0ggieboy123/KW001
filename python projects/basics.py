from tkinter import *
if __name__ == "__main__":
    root = Tk()
    root.title("test")
    root.geometry("350x200")
    label = Label(root,text = "hello")
    label.grid(column = 0,row = 0)
    text = Entry(root,width = 10)
    text.grid(column = 1,row = 0)
    root.mainloop()


