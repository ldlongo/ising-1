import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

magnet={} #magnetizacion


archivo=["M-T.txt"] #"Temperatura -Magnetizacion prom <m>"
        

#extraigo del archivo M-T
for i in range(0,1):
 f=open(archivo[i],'r')
 lines=f.readlines()[1:]
 
 t=[]
 mprom=[]
 dmprom=[]
 
 for line in lines: 
      p = line.split()
      t.append(float(p[0]))
      mprom.append(float(p[1]))
      dmprom.append(float(p[2]))
 tv=np.array(t)
 mv=np.array(mprom)
 dmv=np.array(dmprom)
 magnet[i]=[tv,mv,dmv] 
 f.close()

#Magnet teorica
H=1#campo
temp=np.linspace(0.1, 5.0, 50)
mteorica=[]

for i in range(0,len(temp)):
 #mteorica.append((1/magnet[0][0][i])*np.tanh(1/magnet[0][0][i]))
 mteorica.append(np.tanh(H/temp[i])) #recordar que en el argumento es
                                             #tanh(H*beta)
 
#Grafico eteorica
plt.plot(temp,mteorica,'g',label="solucion exacta")
 

#Grafico MvsT
plt.errorbar(magnet[0][0], magnet[0][1], magnet[0][2],color='r')
plt.plot(magnet[0][0],magnet[0][1],'ro')
plt.plot(magnet[0][0],magnet[0][1],'b',label="solucion numerica")
plt.xlabel("Temperatura")
plt.ylabel("Magnetizacion promedio <m>")

plt.legend()
plt.show()

