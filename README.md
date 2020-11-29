# 無線通訊網路 Project2
This is a project from ncku wireless class.

## Env
* Env:`windows 10 home`
* compiler:`VSCode`
* Language:`c++`、`python`

## Project 目的
使用程式模擬handoff機制
1. **policy 1: Best Strength**
2. **policy 2: Threshold**
3. **policy 3: Entropy**
4. **policy 4: My own**

## 如何模擬
透過在10*10的地圖上不停生成車子單位，並使車子在地圖上一直移動，同時計算車子和地圖上給予的4座基地台之間的Power，然後查看在各不同Policy底下handoff的情形。
## 程式執行
### 產生資料
產生`data.csv`的資料，`data.csv`的每一列都是不同機制和不同lambda值的模擬數據
- compile：`g++ p2.cpp -O3 -o p2.exe`
- run：`./p2.exe`
### 圖形製作
跑完指令後會在`pic`資料夾底下生成12張圖片
- run:`python graph.py`
