#draw a table with the given data and column names in the given order
#(the order of the column names determines the order of the columns)
#the first row is the header row and is bolded and centered by default

import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches
import six


def draw_table(data, col_names, row_names, loc='center', col_width=2.5, row_height=0.625, font_size=14,
               row_colors=['w', 'w'], edge_color='k', bbox=[0, 0, 1, 1], header_color='#40466e',
               ax=None, **kwargs):
    """
    Draw a table with the given data and column names in the given order
    (the order of the column names determines the order of the columns)
    the first row is the header row and is bolded and centered by default
    """
    if ax is None:
        size = (np.array([len(col_names), len(data)+1]) * np.array([col_width, row_height]))
        fig, ax = plt.subplots(figsize=size)
        ax.axis('off')

    mpl_table = ax.table(cellText=data, bbox=bbox, colLabels=col_names, rowLabels=row_names, cellLoc=loc, **kwargs)

    mpl_table.auto_set_font_size(False)
    mpl_table.set_fontsize(font_size)

    for k, cell in six.iteritems(mpl_table._cells):
        cell.set_edgecolor(edge_color)
        if k[0] == 0 or k[1] < 0:
            cell.set_text_props(weight='bold', color='w')
            cell.set_facecolor(header_color)
        else:
            cell.set_facecolor(row_colors[k[0]%len(row_colors) ])
    return ax

#read data from a txt file
a = np.loadtxt('sequential.txt')
b = np.loadtxt('time_4_threads.txt')
c = np.loadtxt('time_8_threads.txt')
d = np.loadtxt('time_16_threads.txt')

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

# raw labels for the table
def get_labels(row):
    labels = []
    for i in range(0, row):
        labels.append(' ')
    return labels

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
data = np.zeros((row, col))
for i in range(0, row):
    data[i][0] = x[i]
    data[i][1] = y[i]

# 4 threads
data1 = np.zeros((row1, col1))
for i in range(0, row1):
    data1[i][0] = x1[i]
    data1[i][1] = y1[i]

# 8 threads
data2 = np.zeros((row2, col2))
for i in range(0, row2):
    data2[i][0] = x2[i]
    data2[i][1] = y2[i]

# 16 threads
data3 = np.zeros((row3, col3))
for i in range(0, row3):
    data3[i][0] = x3[i]
    data3[i][1] = y3[i]

# secuencial
data = np.around(data, decimals=5)
data = data.tolist()

# 4 threads
data1 = np.around(data1, decimals=5)
data1 = data1.tolist()

# 8 threads
data2 = np.around(data2, decimals=5)
data2 = data2.tolist()

# 16 threads
data3 = np.around(data3, decimals=5)
data3 = data3.tolist()

# secuencial
col_labels = ['N', 'Tiempo (s)']
row_labels = get_labels(row)

# 4 threads
col_labels1 = ['N', 'Tiempo (s)']
row_labels1 = get_labels(row1)

# 8 threads
col_labels2 = ['N', 'Tiempo (s)']
row_labels2 = get_labels(row2)

# 16 threads
col_labels3 = ['N', 'Tiempo (s)']
row_labels3 = get_labels(row3)

# secuencial
table = draw_table(data, col_labels, row_labels, loc='center', col_width=2.5, row_height=0.625, font_size=14, edge_color='k', bbox=[0, 0, 1, 1], header_color='#40466e')
plt.savefig('sequential.png', dpi=300, bbox_inches='tight')

# 4 threads
table1 = draw_table(data1, col_labels1, row_labels1, loc='center', col_width=2.5, row_height=0.625, font_size=14, edge_color='k', bbox=[0, 0, 1, 1], header_color='#40466e')
plt.savefig('4threads.png', dpi=300, bbox_inches='tight')

# 8 threads
table2 = draw_table(data2, col_labels2, row_labels2, loc='center', col_width=2.5, row_height=0.625, font_size=14, edge_color='k', bbox=[0, 0, 1, 1], header_color='#40466e')
plt.savefig('8threads.png', dpi=300, bbox_inches='tight')

# 16 threads
table3 = draw_table(data3, col_labels3, row_labels3, loc='center', col_width=2.5, row_height=0.625, font_size=14, edge_color='k', bbox=[0, 0, 1, 1], header_color='#40466e')
plt.savefig('16threads.png', dpi=300, bbox_inches='tight')



# show the table
plt.show()

