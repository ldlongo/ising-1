import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

magnet={} #magnetizacion

iteraciones="32.txt"
#J acoplamiento
J=1.00
#tamano
n=32
#extraigo iteracion
f=open(iteraciones,'r')
lines=f.readlines()[1:]

key=[]
archivo=[]

for line in lines:
    p=line.split()
    key.append("%d" % float(p[0]))
    archivo.append("M-T"+"-"+"%d" % float(n)+"-"+"%0.2f" % float(J)+"-"+"%d" % float(p[0])+".txt")
        

#extraigo del archivo M-T
for i in range(0,len(key)):
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

#colores
color=['bo','ro','yo','mo','co','go','ko','ro']
colorline=['b','r','y','m','c','g','k','r']


#Grafico MvsT
for i in range(0,len(key)):
 #plt.errorbar(magnet[i][0], magnet[i][1], magnet[i][2],color='r')
 plt.plot(magnet[i][0],magnet[i][1],color[i],label=key[i])
 plt.plot(magnet[i][0],magnet[i][1],colorline[i])
plt.xlabel(r'$Temperatura$', fontsize=20)
plt.ylabel(r'$Magnetizacion$'+' '+r'$<m>$', fontsize=20)
plt.text(0.5, 0.0025, r'$Tamano$'+' '+r'$n=32$', fontsize=20, bbox=dict(facecolor='r', alpha=0.3))
plt.legend(loc='lower left')
plt.show()
4
