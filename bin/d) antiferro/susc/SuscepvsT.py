import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

suscep={} #susceptibilidad

tamano="tamano.txt"
#acoplamiento
J=-1.00
#extraigo acople
f=open(tamano,'r')
lines=f.readlines()[1:]

key=[]
archivo=[]

for line in lines:
    p=line.split()
    key.append("%d" % float(p[0]))
    archivo.append("M-T"+"-"+"%d" % float(p[0]) +"-"+"%0.2f" % float(J)+".txt")

        

#extraigo de los archivos E-T
for i in range(0,len(key)):
 f=open(archivo[i],'r')
 lines=f.readlines()[1:]
 
 t=[]
 sus=[]
 #deprom=[]
 
 for line in lines: 
      p = line.split()
      t.append(float(p[0]))
      sus.append(float(p[2])*float(p[2])/(float(p[0])*float(p[0])))
      
 tv=np.array(t)
 susv=np.array(sus)
 suscep[i]=[tv,susv] 
 f.close()


#colores
color=['bo','ro','yo','mo','co','go','ko','ro']
colorline=['b','r','y','m','c','g','k','r']


#Grafico EvsT
for i in range(0,len(key)):
 #plt.errorbar(energia[i][0], energia[i][1], energia[i][2],color=colorline[i])
 plt.plot(suscep[i][0],suscep[i][1],color[i],label=key[i])
 plt.plot(suscep[i][0],suscep[i][1],colorline[i]) 
plt.xlabel(r'$Temperatura$', fontsize=20)
plt.ylabel(r'$Susceptibilidad$'+' '+r'$\chi$', fontsize=20)
plt.text(5.5, 0.00016, r'$Tamanos$'+' '+r'$n$', fontsize=20, bbox=dict(facecolor='g', alpha=0.3)) 
plt.legend(loc='upper right')
plt.show()


