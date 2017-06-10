import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

calor={} #calor

#acople
J=1.00
#tamano
tamano="tamano.txt"

#extraigo acoples
f=open(tamano,'r')
lines=f.readlines()[1:]

key=[]
archivo=[]

for line in lines:
    p=line.split()
    key.append("%d" % int(p[0]))
    archivo.append("E-T"+"-"+"%d" % int(p[0])+"-"+"%0.2f" % float(J)+".txt")

        

#extraigo de los archivos E-T
for i in range(0,len(key)):
 f=open(archivo[i],'r')
 lines=f.readlines()[1:]
 
 t=[]
 ce=[]
 #deprom=[]
 
 for line in lines: 
      p = line.split()
      t.append(float(p[0]))
      #ce.append(float(p[3])/(float(key[i])*float(key[i])))
      ce.append(float(p[2])*float(p[2])/(float(p[0])*float(p[0])))
      
 tv=np.array(t)
 cev=np.array(ce)
 calor[i]=[tv,cev] 
 f.close()


#colores
color=['bo','ro','yo','mo','co','go','ko','ro']
colorline=['b','r','y','m','c','g','k','r']


#Grafico EvsT
for i in range(0,len(key)):
 #plt.errorbar(energia[i][0], energia[i][1], energia[i][2],color=colorline[i])
 plt.plot(calor[i][0],calor[i][1],colorline[i])
 plt.plot(calor[i][0],calor[i][1],color[i],label=key[i]) 
plt.xlabel("Temperatura")
plt.ylabel("calor especifico")
plt.legend(loc='upper right')
plt.text(2.5, 0.0065, r'$Tamanos$'+' '+r'$J$', fontsize=20, bbox=dict(facecolor='g', alpha=0.3)) 
plt.show()


