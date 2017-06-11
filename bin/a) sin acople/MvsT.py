import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

magnet={} #magnetizacion


archivo=["M-T-32-0.00.txt"] #"Temperatura -Magnetizacion prom <m>"
        

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
 mteorica.append(np.tanh(H/temp[i])) #recordar que en el argumento es
                                             #tanh(H*beta)
 
#Grafico mteorica
plt.plot(temp,mteorica,'r',label="solucion exacta")
 

#Grafico MvsT
plt.errorbar(magnet[0][0], magnet[0][1], magnet[0][2], fmt='o', color='r',label="solucion numerica")
plt.xlabel(r'$Temperatura$', fontsize=20)
plt.ylabel(r'$Magnetizacion$'+' '+r'$<m>$', fontsize=20)
plt.text(3.5, 0.78, r'$<m> = tanh(\frac{B}{kT})$', fontsize=20, bbox=dict(facecolor='r', alpha=0.3))
plt.legend()
plt.show()

