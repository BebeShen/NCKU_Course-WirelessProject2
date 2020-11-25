# Wireless Class Project2
This is a project from ncku wireless class.

## Env
* Env:`windows 10 home`
* compiler:`VSCode`
* Language:`gcc 9.2.0`

## Purpose
Use program to simulate handoff policy
1. **policy 1: Best Strength**
2. **policy 2: Threshold**
3. **policy 3: Entropy**

## How to Simulate
Given a 10*10 metrix, (0,0)~(1000,1000) 100 per block, entry points are all on edge, with the poisson arrival rate: [1/2,1/3,1/5] of car at each entry.

every car has velocity 10 m per s , and once it reach a intersection , it has 0.6 of prob keep forward,0.2 turn left,0.2turn right.

and 4 base station with power = 100 .

## Run
- compile：`g++ p2.cpp -O3 -o p2.exe`
- run：`./p2.exe`

## TODO
1. Policy implement
2. Record handoff
3. find best E and T
4. My own policy