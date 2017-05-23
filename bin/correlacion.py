import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

datos={} #energia-magnetizacion
corr={}  #correlacion

archivo=["1.50-0.00.txt"]
archivocor=["corr1.50-0.00.txt"]
key=['1.00']                  #temperatura-campo

#extraigo del archivocorr
for i in range(0,len(key)):
 f=open(archivocor[i],'r')
 lines=f.readlines()[1:]
 
 x=[]
 y=[]
 pasos=[]
 for line in lines: 
      p = line.split()
      x.append(float(p[0]))
      y.append(float(p[1]))
 xv=np.array(x)
 yv=np.array(y)
 corr[key[i]]=[xv,yv] 
 f.close()
 
print corr[key[0]][1]
#extraigo del archivo
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
 datos[key[i]]=[ev,mv] 
 f.close()

#vector de pasos 
for i in range(0,len(datos[key[0]][0])):
 pasos.append(i)
 
#Grafico Energia      
plt.figure(0)
plt.plot(pasos,datos[key[0]][0],'bo')
plt.ylabel("Energia")
#Grafico Magnetizacion      
plt.figure(1)
plt.plot(pasos,datos[key[0]][1],'ro')
plt.ylabel("Magnetizacion") 
#Grafico correlacion
plt.figure(2)
plt.plot(corr[key[0]][0],corr[key[0]][1],'mo')
plt.ylabel("Correlacion")

plt.show()
