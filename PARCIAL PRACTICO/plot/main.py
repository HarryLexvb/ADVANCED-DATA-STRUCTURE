import numpy as np
import matplotlib.pyplot as plt


#plt.style.use('seaborn')

a = np.loadtxt('time.txt')
b = np.loadtxt('time1.txt')
row = (a.shape)[0] #numero de filas 
col = (a.shape)[1] #numero de columnas
row1 = (b.shape)[0] #numero de filas 
col1 = (b.shape)[1] #numero de columnas


x = np.zeros(row)
y = np.zeros(row)

x1 = np.zeros(row1)
y1 = np.zeros(row1)

for i in range(0,row):
  x[i] = a[i][0]
  y[i] = a[i][1]

for i in range(0,row1):
  x1[i] = b[i][0]
  y1[i] = b[i][1]

plt.plot(x,y, color='red', linestyle='dashed', linewidth=2,marker='o',markersize=6,markerfacecolor='blue',markeredgecolor='blue')

"""plt.plot(x1,y1, color='green', linestyle='dashed', linewidth=2,marker='o',markersize=6,markerfacecolor='black',markeredgecolor='black')"""

plt.grid()
plt.show()
