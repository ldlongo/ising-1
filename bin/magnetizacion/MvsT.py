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

#Grafico MvsT
plt.errorbar(magnet[0][0], magnet[0][1], magnet[0][2],color='r')
plt.plot(magnet[0][0],magnet[0][1],'ro')
plt.plot(magnet[0][0],magnet[0][1],'b')
plt.xlabel("Temperatura")
plt.ylabel("Magnetizacion promedio <m>")
plt.show()

