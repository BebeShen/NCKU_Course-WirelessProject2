import math
class car:
    v = 10
    Pf = 0.6
    Pl = 0.2
    Pr = 0.2
    def __init__(self,x,y):
        self.x = x
        self.y = y
class base:
    power = 100
    def __init__(self,x,y):
        self.x = x
        self.y = y


def receiveGain(D):
    return 32.45+20*math.log10(D)
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
handoff = []
# grid = [[0]*10]*10

### policy:Best