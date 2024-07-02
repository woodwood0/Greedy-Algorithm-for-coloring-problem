# Greedy Algorithm for coloring problem

此專案以Greedy Algorithm貪婪演算法求解著色問題，規則為對未上色的節點著色，但相鄰連接的節點不可同色，顏色種類最多與節點數量一樣，目標為找出最少種顏色的塗法。
<br>

## Greedy Algorithm貪婪演算法
### 2024/07/02 update
1. 釋放記憶體<br>
   修正`result` 和 `available` 陣列使用 `new` 動態分配記憶體，但沒有對應的 `delete` 操作來釋放記憶體。<br>
   
2. 使用結構(struct)封裝變數<br>
   增加可讀性和可測試性。(原先無法簡單地透過查看函數的參數來了解函數的行為，且在進行單元測試時，靜態變數的狀態需要被重置，這增加了編寫測試代碼的難度。)<br>
   
3. 改善效率<br>
   避免每次都初始化 `available` 陣列和 `result` 陣列，將其移至 `main` 函數。<br>
   使用 `vector<int>` 取代 `list<int>`。<br>

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
![圖片1](https://github.com/woodwood0/Greedy-Algorithm-for-coloring-problem/assets/171545924/a8531f04-19cc-4a68-bae1-046c96b90055)
<br>
<br>
