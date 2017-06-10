import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

magnet={} #magnetizacion


archivo=["histo15000.txt"] #"Temperatura -Magnetizacion prom <m>"
        

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
 tv=np.array(t)
 mv=np.array(mprom)
 magnet[i]=[tv,mv] 
 f.close()
 

#Histograma
a=-1.05 #extremo inf
b=1.05  #extremo sup
n=len(magnet[0][1])#numero de puntos
print n
numbin=75
s=("%0.6f" % float(1.0/n)) #cuenta normalizada str
hbin=("%0.3f" % float((b-a)/float(numbin-1))) #anchobin


hcentro=np.zeros(numbin)
hcuenta=np.zeros(numbin)


#Lleno centros
for i in range(0,numbin):
    hcentro[i]=(i*float(hbin)+(float(hbin)/2.0))+a-(float(hbin)/2.0)


#Recorro el vector de datos magnet[0][1]
for i in range(0,len(magnet[0][1])):
 j=(magnet[0][1][i]-a)//float(hbin)
 if (j<0):
  j=0
 if (j>numbin):
  j=numbin-1
 hcuenta[int(j)]=hcuenta[int(j)]+float(s)


#Grafico MvsT
plt.figure(1)
plt.plot(magnet[0][0],magnet[0][1],'ro')
plt.plot(magnet[0][0],magnet[0][1],'b')
plt.xlabel("Temperatura")
plt.ylabel("Magnetizacion promedio <m>")


#Grafico Histograma:
plt.figure(2)
plt.bar(hcentro,hcuenta,float(hbin))
plt.xlabel("Magnetizacion promedio <M>")
plt.ylabel("Frecuencia normalizada")
plt.show()




