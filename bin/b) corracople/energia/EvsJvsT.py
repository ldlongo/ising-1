import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

energia={}  #energia

acople="acople.txt"

#tamano
n=32

#extraigo j
f=open(acople,'r')
lines=f.readlines()[1:]

key=[]
archivo=[]

for line in lines:
    p=line.split()
    key.append("%0.2f" % float(p[0]))
    archivo.append("E-T-"+"%d" %int(n)+"-"+"%0.2f" % float(p[0])+".txt")
    

#extraigo del archivocorr
for i in range(0,len(key)):
 f=open(archivo[i],'r')
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
 energia[key[i]]=[xv,yv] 
 f.close()


#colores
color=['bo','ro','yo','mo','co','go','ko','ro']
colorline=['b','r','y','m','c','g','k','r']

#Grafico Magnet
for i in range(0,len(key)):
 plt.plot(energia[key[i]][0],energia[key[i]][1],color[i],label=key[i])
 plt.plot(energia[key[i]][0],energia[key[i]][1],colorline[i])
plt.xlabel(r'$Temperatura$', fontsize=20)
plt.ylabel(r'$Energia$'+' '+ r'$<e>$', fontsize=20)
plt.text(2.5, 0.2, r'$Acoplamiento$'+' '+r'$J$', fontsize=20, bbox=dict(facecolor='b', alpha=0.3)) 
plt.legend(loc='lower right',numpoints=1)

plt.show()


