import matplotlib.pyplot as plt
import numpy as np
import csv

# 設置 x 軸
x = []
y = []
# x = np.array()
# y = np.array()

with open('data.csv', newline='') as csvfile:
    rows = csv.reader(csvfile, delimiter=',')
    for row in rows:
        x.append(int(row[0]))
        y.append(int(row[1]))
plt.plot(x,y,label='Loaded from file!')
plt.xlabel('Time(sec)')
plt.ylabel('# of Handoff')
plt.show()
#         handoff = np.array(row)
#         # 設置 y 軸
#         print(handoff,type(handoff))
#         plt.plot(TimeLine,handoff,marker = 'o')
#         plt.show()