import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

energia={} #energia


archivo=["E-T-32-0.00.txt"] #"Temperatura -Energia prom <m>"
        

#extraigo del archivo E-T
for i in range(0,1):
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

#Energia teorica
H=1; #campo 
temp=np.linspace(0.1, 5.0, 50)
eteorica=[]

for i in range(0,len(temp)):
 #eteorica.append((1/magnet[0][0][i])*np.tanh(1/magnet[0][0][i]))
 eteorica.append(-H*np.tanh(H/temp[i])) #recordar que e es
                                             #-H*tanh(H*beta)
 
#Grafico eteorica
plt.plot(temp,eteorica,'b',label="solucion exacta")
  

#Grafico EvsT
plt.errorbar(energia[0][0], energia[0][1], energia[0][2], fmt='o',color='b',label="solucion numerica")
plt.xlabel(r'$Temperatura$',fontsize=20)
plt.ylabel(r'$Energia$'+' '+r'$<e>$',fontsize=20)
plt.text(2.5,-0.6, r'$<e>=B$'+' '+r'$tanh(\frac{B}{kT})$', fontsize=20, bbox=dict(facecolor='b', alpha=0.3))
plt.legend(loc='upper left',numpoints=1)
plt.show()

