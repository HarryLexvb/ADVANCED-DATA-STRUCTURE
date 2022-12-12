import numpy as np
import matplotlib.pyplot as plt

# plt.style.use('seaborn')

a = np.loadtxt('sequential.txt')  # version secuencial
b = np.loadtxt('time_4_threads.txt')  # 4 threads
c = np.loadtxt('time_8_threads.txt')  # 8 threads
d = np.loadtxt('time_16_threads.txt')  # 16 threads

# secuencial
row = (a.shape)[0]  # numero de filas
col = (a.shape)[1]  # numero de columnas

# 4 threads
row1 = (b.shape)[0]  # numero de filas
col1 = (b.shape)[1]  # numero de columnas

# 8 threads
row2 = (c.shape)[0]  # numero de filas
col2 = (c.shape)[1]  # numero de columnas

# 16 threads
row3 = (d.shape)[0]  # numero de filas
col3 = (d.shape)[1]  # numero de columnas

# secuencial
x = np.zeros(row)
y = np.zeros(row)

# 4 threads
x1 = np.zeros(row1)
y1 = np.zeros(row1)

# 8 threads
x2 = np.zeros(row2)
y2 = np.zeros(row2)

# 16 threads
x3 = np.zeros(row3)
y3 = np.zeros(row3)

# secuencial
for i in range(0, row):
  x[i] = a[i][0]
  y[i] = a[i][1]

# 4 threads
for i in range(0, row1):
  x1[i] = b[i][0]
  y1[i] = b[i][1]

# 8 threads
for i in range(0, row2):
  x2[i] = c[i][0]
  y2[i] = c[i][1]

# 16 threads
for i in range(0, row3):
  x3[i] = d[i][0]
  y3[i] = d[i][1]

# secuencial
plt.plot(x,
         y,
         label='secuencial',
         color='red',
         linestyle='dashed',
         marker='o',
         markerfacecolor='blue',
         markeredgecolor='blue')

# 4 threads
plt.plot(x1,
         y1,
         label='4 threads',
         color='green',
         linestyle='dashed',
         marker='o',
         markerfacecolor='black',
         markeredgecolor='black')

# 8 threads
plt.plot(x2,
         y2,
         label='8 threads',
         color='brown',
         linestyle='dashed',
         marker='o',
         markerfacecolor='red',
         markeredgecolor='red')

# 16 threads
plt.plot(x3,
         y3,
         label='16 threads',
         color='blue',
         linestyle='dashed',
         marker='o',
         markerfacecolor='green',
         markeredgecolor='green')

plt.xlabel('Tamaño de la matriz')
plt.ylabel('Tiempo (segundos)')
plt.title('Tiempo de ejecución')
plt.legend()
plt.grid()
plt.show()
