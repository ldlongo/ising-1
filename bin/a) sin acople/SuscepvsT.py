import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

suscep={} #susceptibilidad

tamano="tamano.txt"
#J acoplamiento
J=0.00
#extraigo tamanos
f=open(tamano,'r')
lines=f.readlines()[1:]

key=[]
archivo=[]

for line in lines:
    p=line.split()
    key.append("%d" % float(p[0]))
    archivo.append("M-T"+"-"+"%d" % float(p[0])+"-"+"%0.2f" % float(J)+".txt")

        

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
      sus.append(float(p[3]))
      
 tv=np.array(t)
 susv=np.array(sus)
 suscep[i]=[tv,susv] 
 f.close()

#Susc teorica
H=1; #campo 
temp=np.linspace(0.1, 5.0, 50)
suscteorica=[]

for i in range(0,len(temp)):
 #cteorica.append((1/magnet[0][0][i])*np.tanh(1/magnet[0][0][i]))
 suscteorica.append(float(key[0])*float(key[0])*(1/(temp[i]))*((1-(np.tanh(H/temp[i])*np.tanh(H/temp[i]))))) #Susc=N*d(m)/dB
 
#Grafico cteorica
plt.plot(temp,suscteorica,'g',label="solucion exacta")

#colores
color=['go','ro','yo','mo','co','go','ko','ro']
colorline=['b','r','y','m','c','g','k','r']


#Grafico SuscvsT
for i in range(0,len(key)):
 plt.plot(suscep[i][0],suscep[i][1],color[i],label="solucion numerica") 
plt.xlabel(r'$Temperatura$', fontsize=20)
plt.ylabel(r'$Susceptibilidad$'+' '+r'$\chi$', fontsize=20)
plt.text(3.4,355, r'$\chi=\frac{N}{kT}[1-tanh^2(\frac{B}{kT})]$', fontsize=20, bbox=dict(facecolor='g', alpha=0.3))
plt.legend(loc='upper right')
plt.show()


