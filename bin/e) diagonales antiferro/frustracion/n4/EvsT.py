import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

energia={} #energia

iteraciones="4.txt"
#J acoplamiento
J=1.00
#tamanos
n=4
#extraigo iteraciones
f=open(iteraciones,'r')
lines=f.readlines()[1:]

key=[]
archivo=[]

for line in lines:
    p=line.split()
    key.append("%d" % float(p[0]))
    archivo.append("E-T"+"-"+"%d" % float(n)+"-"+"%0.2f" % float(J)+"-"+"%d" %float(p[0])+".txt")

        

#extraigo de los archivos E-T
for i in range(0,len(key)):
 f=open(archivo[i],'r')
 lines=f.readlines()[1:]
 
 t=[]
 eprom=[]
 deprom=[]
 
 for line in lines: 
      p = line.split()
      t.append(float(p[0]))
      eprom.append(float(p[1]))
      deprom.append(float(p[2]))
 tv=np.array(t)
 ev=np.array(eprom)
 dev=np.array(deprom)
 energia[i]=[tv,ev,dev] 
 f.close()


#colores
color=['bo','ro','yo','mo','co','go','ko','ro']
colorline=['b','r','y','m','c','g','k','r']


#Grafico EvsT
for i in range(0,len(key)):
 #plt.errorbar(energia[i][0], energia[i][1], energia[i][2],color=colorline[i])
 plt.plot(energia[i][0],energia[i][1],color[i],label=key[i]) 
plt.xlabel(r'$Temperatura$', fontsize=20)
plt.ylabel(r'$Energia$'+' '+r'$<e>$', fontsize=20)
plt.legend(loc='lower right', numpoints=1)
plt.text(0.5, -0.8, r'$Tamano$'+' '+ r'$n=4$', fontsize=20, bbox=dict(facecolor='r', alpha=0.3))
plt.show()


