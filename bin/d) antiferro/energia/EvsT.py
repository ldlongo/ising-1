import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

energia={} #energia

tamano="tamano.txt"
#J acoplamiento
J=-1.00
#extraigo tamanos
f=open(tamano,'r')
lines=f.readlines()[1:]

key=[]
archivo=[]

for line in lines:
    p=line.split()
    key.append("%d" % float(p[0]))
    archivo.append("E-T"+"-"+"%d" % float(p[0])+"-"+"%0.2f" % float(J)+".txt")

        

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
plt.xlabel("Temperatura")
plt.ylabel("Energia promedio <e>")
plt.legend(loc='lower right')
plt.show()


