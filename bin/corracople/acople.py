import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

corr={}  #correlacion

acople="acople.txt"

#Temepratura
T=2.26
#extraigo j
f=open(acople,'r')
lines=f.readlines()[1:]

key=[]
archivo=[]
archivocorr=[]

for line in lines:
    p=line.split()
    key.append("%0.2f" % float(p[0]))
    archivo.append("%0.2f" %float(T)+"-"+"%0.2f" % float(p[0])+".txt")
    archivocorr.append("corr"+"%0.2f" %float(T)+"-"+"%0.2f" % float(p[0])+".txt")


#extraigo del archivocorr
for i in range(0,len(key)):
 f=open(archivocorr[i],'r')
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


#colores
color=['bo','ro','yo','mo','co','go','ko','ro']


#Grafico Correlacion
for i in range(0,len(key)):
 plt.plot(corr[key[i]][0],corr[key[i]][1],color[i],label=key[i])
plt.xlabel("k")
plt.ylabel("Correlacion")
plt.legend(numpoints=1)

plt.show()


