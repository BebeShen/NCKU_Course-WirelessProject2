import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import csv

colors = ['b','g','r','b']
# 設置 x 軸
# x = [i for i in range(1,86401,1)]
# y = []
x = np.linspace(0,86400,86400)
# x = np.array(x)
# y = np.array(y)
i = 0
path = ""
paras = {'xtick.labelsize':8,'ytick.labelsize':8,'axes.titlesize':12,'axes.labelsize':10}
plt.rcParams.update(paras)
# fig = plt.figure(figsize=(8, 6))
with open('data.csv', newline='') as csvfile:
    rows = csv.reader(csvfile, delimiter=',')
    for row in rows:
        handoff = np.array(row)
        for j in range(0, len(handoff)): 
            handoff[i] = int(handoff[i]) 
        # 設置 y 軸
        plt.figure(figsize=(8,6))
        plt.axis('auto')    
        plt.locator_params(tight = True)
        plt.plot(x,handoff,colors[int(i/3)])
        ax = plt.gca()
        if i < 3:  
            ax.set_title('BestPolicy Handoff per Hour')
        elif i < 6: 
            ax.set_title('Threshold Handoff per Hour')
        elif i < 9: 
            ax.set_title('Entropy Handoff per Hour')
        elif i < 12: 
            ax.set_title('MyPolicy Handoff per Hour')
        
        ax.set_xlabel('Hour')
        ax.set_ylabel('Handoff')
        ax.set_xticks(np.linspace(0,86400,24))
        ax.set_xticklabels([str(i+1) for i in range(24)])
        if i < 3:  
            path = "./pic/BestPolicy"+str(i%3+1)+".png"
        elif i < 6: 
            path = "./pic/Threshold"+str(i%3+1)+".png"
        elif i < 9: 
            path = "./pic/Entropy"+str(i%3+1)+".png"
        elif i < 12: 
            path = "./pic/MyPolicy"+str(i%3+1)+".png"
        i+=1
        plt.savefig(path)
        # plt.show()
