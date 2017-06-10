import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

calor={} #energia

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
    archivo.append("E-T"+"-"+"%d" % float(p[0])+"-"+"%0.2f" % float(J)+".txt")

#extraigo de los archivos E-T
for i in range(0,len(key)):
 f=open(archivo[i],'r')
 lines=f.readlines()[1:]
 
 t=[]
 ce=[]
 
 for line in lines: 
      p = line.split()
      t.append(float(p[0]))
      ce.append(float(p[3]))
      
 tv=np.array(t)
 cev=np.array(ce)
 calor[i]=[tv,cev] 
 f.close()

#Cv teorica
H=1; #campo 
temp=np.linspace(0.1, 5.0, 100)
cteorica=[]

for i in range(0,len(temp)):
 #cteorica.append((1/magnet[0][0][i])*np.tanh(1/magnet[0][0][i]))
 cteorica.append((H*H/(temp[i]*temp[i]))*((1-(np.tanh(H/temp[i])*np.tanh(H/temp[i]))))) #cv=du/dT
 
#Grafico cteorica
plt.plot(temp,cteorica,'m',label="solucion exacta")

#colores
color=['mo','ro','yo','mo','co','go','ko','ro']
colorline=['b','r','y','m','c','g','k','r']


#Grafico EvsT
for i in range(0,len(key)):
 plt.plot(calor[i][0],calor[i][1],color[i],label='solucion numerica') 
plt.xlabel("Temperatura")
plt.ylabel("Calor especifico")
plt.legend(loc='lower right')
plt.show()


