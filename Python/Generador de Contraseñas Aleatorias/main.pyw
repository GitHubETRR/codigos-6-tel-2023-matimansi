
import tkinter as tk
from PIL import Image, ImageTk
import random
import string

caracteres = list(string.digits + string.ascii_uppercase + string.ascii_lowercase + string.punctuation)

interfaz = tk.Tk()
interfaz.title("Generador de Contraseñas Aleatorias")
interfaz.iconbitmap("Fotos/Agente_Wiggles.ico")
interfaz.geometry("600x200")
interfaz.resizable(0, 0)
interfaz.config(bg = "white", bd = 20)

imagen = Image.open("Fotos/Agente_Wiggles.png")
imagen = imagen.resize((200, 200))
imagen_tk = ImageTk.PhotoImage(imagen)

longitud = tk.StringVar()
contra_generada = tk.StringVar()

def lectura():
	long = int(longitud.get())
	if long > 0 and long < 50:
		generador_contra(long)
	else:
		contra_generada.set("ERROR")

def generador_contra(longitud):
	contra = ""
	for i in range(longitud):
		contra += (random.choice(caracteres))
	contra_generada.set(contra)
 
texto = tk.Label(interfaz, bg = "white", text = "Ingrese la longitud de la contraseña", font = ("Arial", 15, "bold"), fg = "black")
entrada = tk.Entry(interfaz, bg = "white", textvariable = longitud, font = ("Arial", 15, "bold"), fg = "black")
boton = tk.Button(interfaz, text = "Enviar", command = lectura, font = ("Arial", 10, "italic"))
contrasena_label = tk.Entry(interfaz, bg = "white", textvariable = contra_generada, font = ("Arial", 12, "bold"), fg = "black")
rango = tk.Label(interfaz, bg = "white", text = "La longitud de la contraseña debe ser mayor a 0 y menor a 50", font = ("Arial", 10, "italic"), fg = "red")
label_imagen = tk.Label(interfaz, image = imagen_tk)

texto.place(x = 5, y = 5)
entrada.place(x = 35, y = 50)
boton.place(x = 270, y = 50)
contrasena_label.place(x = 35, y = 90, width = 283, height = 30)
rango.place(x = -10, y = 150)
label_imagen.place(x = 378, y = -20)

interfaz.mainloop()
