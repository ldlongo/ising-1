import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

datos={} #energia-magnetizacion
corr={}  #correlacion
tempkey=[]
acopkey=[]
archivocorr=[]

#T temperatura
temp="temp.txt"
#J acoplamiento
acople="acople.txt"
#n tamano
n=32
#extraigo temperaturas

f=open(temp,'r')
lines=f.readlines()[1:]

for line in lines:
    p=line.split()
    tempkey.append("%0.2f" % float(p[0]))

f.close()

#extraigo J
f=open(acople,'r')
lines=f.readlines()[1:]

for line in lines:
    p=line.split()
    acopkey.append("%0.2f" % float(p[0]))

f.close()    

for i in range(0,len(tempkey)):
 for j in range(0,len(acopkey)):
    archivocorr.append("corr"+"%d" %int(n)+"-"+"%0.2f" % float(tempkey[i])+"-"+"%0.2f" % float(acopkey[j])+".txt") #contiene para una temp todas las j y luego la proxima temp


for k in range(0,len(acopkey)):
#extraigo del archivocorr para un mismo J y distintas temp
 for i in range(0,len(tempkey)):
  j=(i*len(acopkey))+k
  f=open(archivocorr[j],'r')
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
  corr[tempkey[i]]=[xv,yv] 
  f.close()

 #colores
 color=['bo','ro','yo','mo','co','go','ko','ro','bo'] 


 #Grafico Correlacion
 plt.figure(k)
 for i in range(0,len(tempkey)):
  plt.plot(corr[tempkey[i]][0],corr[tempkey[i]][1],color[i],label=tempkey[i])
 plt.xlabel("k") 
 plt.ylabel("Correlacion")
 plt.text(10000, 0.9, r'$J=$'+"%0.1f" % float (acopkey[k]), fontsize=20, bbox=dict(facecolor='b', alpha=0.3))
 plt.legend(numpoints=1)

plt.show()

