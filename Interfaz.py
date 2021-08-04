from tkinter import *

class Window(Frame):

    def __init__(self, master=None):
        Frame.__init__(self, master)               
        self.master = master
        self.init_window()

    #Creation of init_window
    def init_window(self):
        # changing the title of our master widget      
        self.master.title("Serial")
        # allowing the widget to take the full space of the root window
        self.pack(fill=BOTH, expand=1)
        # Botón para conectar la comunicación serial
        ConectarButton = Button(self, text="Conectar")
        #Ubicación del botón
        ConectarButton.place(x=10, y=10)
        
        #Botón para enviar datos por USART
        EnviarButton = Button(self, text="Enviar")
        #Ubicación del botón
        EnviarButton.place(x=160, y=80)
        
        #Texto del Contador
        text = Label(self, text="Contador: ").place(x=10, y=50)
        self.name = Entry(text)
        self.name.focus()
        self.name.place(x=10, y=80)
        
        POT_1 = Label(self, text = 'POT1').place(x=50, y = 120)
        POT_2 = Label(self, text = 'POT2').place(x=150, y = 120)
        
root = Tk()
#size of the window
root.geometry("230x200")    
app = Window(root)
root.mainloop()