import math
import time
import random
class car:
    v = 10
    def __init__(self,x,y):
        self.x = x
        self.y = y
        # car's direction up:0,down:1,left:2,right:3
        if y == 0: # go up
            self.dir = 0 
        elif y == 1000: # go down
            self.dir = 1
        elif x == 1000:# go left
            self.dir = 2
        else: # go right
            self.dir = 3
    # TODO 1st base
class base:
    power = 100
    def __init__(self,x,y):
        self.x = x
        self.y = y


def receiveGain(car,pos):
    return 32.45+20*math.log10(pos)
def checkhandoff(car,bases):
    now_base = car.base
    G_0 = receiveGain(car,bases[0])
    G_1 = receiveGain(car,bases[1])
    G_2 = receiveGain(car,bases[2])
    G_3 = receiveGain(car,bases[3])
    most_Pr = max(G_0,G_1,G_2,G_3)
    if most_Pr ==  G_0:
        car.base = 0
    elif most_Pr == G_1:
        car.base = 1
    elif most_Pr == G_2:
        car.base = 2
    elif most_Pr == G_3:
        car.base = 3
    if now_base != car.base:
        return 1
    else:return 0
# set env
entry = []
for i in range(100,1000,100):
    entry.append([i,0])
for i in range(100,1000,100):
    entry.append([i,1000])
for i in range(100,1000,100):
    entry.append([0,i])
for i in range(100,1000,100):
    entry.append([1000,i])
print(entry)
systemTime = 86400*1000
P_min = 10 # dBm
lmd = [(1/2),(1/3),(1/5)]
cars = []
# 4 bases
bases = []
bases.append(base(330,350)) # base 0
bases.append(base(640,310)) # base 1
bases.append(base(360,680)) # base 2
bases.append(base(660,658)) # base 3
handoff = 0
# grid = [[0]*10]*10
### policy 1 :Best Strength  with lmd = 0.5
for k in range(86400):
    random.seed((int)(time.time()))
    # move car
    print(k)
    for i in range(len(cars)):
        moveProb =  random.random()
        # print(moveProb)
        if moveProb <= 0.6: # forward
            pass
        elif moveProb <= 0.8: # left
            pass
        else:
            pass
    # deq if car is at out port
    for i in range(len(cars)-1,-1,-1):
        if cars[i].x == 0 or cars[i].x == 1000 or cars[i].y == 0 or cars[i].y == 1000:
            cars.remove(cars[i])
        # TODO calculate receive Gain
        # TODO count handoff
    # add cars from entry  
    for _ in range(1000):
        prob = random.random()
        if prob < lmd[0]:
            pos = random.randint(0,len(entry)-1)
            cars.append(car(entry[pos][0],entry[pos][1]))
print(cars)
print(handoff)
