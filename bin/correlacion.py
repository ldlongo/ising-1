import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

data={} #diccionario de datos

archivo=["corr2.00-0.00.txt"]
key=['2.00']                  #temperatura-campo

for i in range(0,len(key)):
 f=open(archivo[i],'r')
 lines=f.readlines()[1:]
 
 x=[]
 y=[]   
 for line in lines: 
      p = line.split()
      x.append(float(p[0]))
      y.append(float(p[1]))
 xv=np.array(x)
 yv=np.array(y)
 data[key[i]]=[xv,yv] #resto la pcritica p-pc=xv-pc
 f.close()

#Grafico       
plt.figure(0)
plt.plot(data[key[0]][0],data[key[0]][1],'bo',label=key[0])

plt.show() 


