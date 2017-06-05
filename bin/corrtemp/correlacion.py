import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

datos={} #energia-magnetizacion
corr={}  #correlacion

temp="temp.txt"
#J acoplamiento
J=0.20
#extraigo temperaturas
f=open(temp,'r')
lines=f.readlines()[1:]

key=[]
archivo=[]
archivocorr=[]

for line in lines:
    p=line.split()
    key.append("%0.2f" % float(p[0]))
    archivo.append("%0.2f" % float(p[0])+"-"+"%0.2f" % float(J)+".txt")
    archivocorr.append("corr"+"%0.2f" % float(p[0])+"-"+"%0.2f" % float(J)+".txt")


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
 datos[key[i]]=[ev,mv] 
 f.close()

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


#vector de pasos 
for i in range(0,len(datos[key[0]][0])):
 pasos.append(i)

#colores
color=['bo','ro','yo','mo','co','go','ko','ro'] 

'''
#Grafico Energia 
plt.figure(0)
for i in range(0,len(key)):  
 plt.plot(pasos,datos[key[i]][0],color[i],label=key[i])
plt.ylabel("Energia")
plt.legend(numpoints=1)
'''
'''
#Grafico Magnetizacion      
plt.figure(1)
for i in range(0,len(key)):
 plt.plot(pasos,datos[key[i]][1],color[i],label=key[i])
plt.ylabel("Magnetizacion")
plt.legend(numpoints=1)
plt.show()

'''

#Grafico Correlacion
for i in range(0,len(key)):
 plt.plot(corr[key[i]][0],corr[key[i]][1],color[i],label=key[i])
plt.xlabel("k") 
plt.ylabel("Correlacion")
plt.legend(numpoints=1)

plt.show()

