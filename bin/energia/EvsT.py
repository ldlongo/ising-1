import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

energia={} #energia


archivo=["E-T.txt"] #"Temperatura -Energia prom <m>"
        

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

#Grafico MvsT
plt.errorbar(energia[0][0], energia[0][1], energia[0][2],color='r')
plt.plot(energia[0][0],energia[0][1],'ro')
plt.plot(energia[0][0],energia[0][1],'b')
plt.xlabel("Temperatura")
plt.ylabel("Energia promedio <m>")
plt.show()

