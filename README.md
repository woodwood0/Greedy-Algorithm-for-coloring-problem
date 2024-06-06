# Greedy Algorithm for coloring problem

此專案以Greedy Algorithm貪婪演算法求解著色問題，規則為對未上色的節點著色，但相鄰連接的節點不可同色，顏色種類最多與節點數量一樣，目標為找出最少種顏色的塗法。
<br>

## Greedy Algorithm貪婪演算法
### 流程

1. **尋找起始點**<br>
   實驗組 : 整理資料後，找出擁有最多連結的節點，將該點作為第一個點開始上色。<br>
   對照組 : 將資料中第一筆資料作為第一個點開始上色。<br>

2. **為節點著色**<br>
   將相鄰節點已使用的顏色標記為不可用，尋找其他可用顏色，為當前節點i 著色。<br>

3. **直到所有節點被著色**<br>
    重置相鄰節點已使用的顏色為不可用，重複步驟2 及步驟3，直到所有節點被著色為止。<br>


### 檔案說明
- 輸入資料 : 編碼方式如圖。<br>
![圖片1](https://github.com/woodwood0/Greedy-Algorithm-for-coloring-problem/assets/171545924/aa21033a-3bff-422c-9168-e998a00c3806)
<br>
<br>
