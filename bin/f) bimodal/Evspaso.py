import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit


datos={} #energia y magnet

#tamano
n=32
#acople
J=0.99


temp="temp.txt"

#extraigo temperaturas
f=open(temp,'r')
lines=f.readlines()[1:]

key=[]
archivo=[]

for line in lines:
    p=line.split()
    key.append("%0.2f" % float(p[0]))
    archivo.append("%d" %int(n)+"-"+"%0.2f" % float(p[0])+"-"+"%0.2f"%float(J)+".txt")
        

#extraigo del archivo energia y magnetizacion

for i in range(0,len(key)):
 f=open(archivo[i],'r')
 lines=f.readlines()[1:]
 
 e=[]
 m=[]
 pasos=[]
 for line in lines: 
      p = line.split()
      e.append(float(p[0]))
      m.append(float(p[1]))
 ev=np.array(e)
 mv=np.array(m)
 datos[i]=[ev,mv] 
 f.close()


#vector pasos
 for i in range(0,len(datos[0][0])):
  pasos.append(i)


#Grafico magnet vs pasos:
for i in range(0,len(key)): 
  plt.plot(pasos,datos[i][1],'o',label=key[i])
  
plt.xlabel("paso")
plt.ylabel("magnetizacion por nodo")
plt.legend()
plt.show()

