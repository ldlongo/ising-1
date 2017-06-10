import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

datos={} #energia-magnetizacion
corr={}  #correlacion

tamano="tamano.txt"
#J acoplamiento
J=0.30
T=2.26
#extraigo tamanos
f=open(tamano,'r')
lines=f.readlines()[1:]

key=[]
archivocorr=[]

for line in lines:
    p=line.split()
    key.append("%d" % float(p[0]))
    archivocorr.append("corr"+"%d" % float(p[0])+"-"+"%0.2f" % float(T)+"-"+"%0.2f" % float(J)+".txt")


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
plt.text(55000, 0.85, r'$Tamanos$'+' '+r'$J$', fontsize=20, bbox=dict(facecolor='g', alpha=0.3)) 
plt.show()

