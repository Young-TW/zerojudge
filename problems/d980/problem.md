# d980. 11479 - Is this the easiest problem?

## 內容

三角形是一種有三個正邊的幾何形狀。但是並非任意三個邊都可以形成一個三角形，這三個邊必需構成一個封閉區域。三角形可以其邊長來分類，本題便是要你判定三角形的種類。

## 輸入說明

輸入的第一行有一個正整數 T<20，表示有 T 筆測試資料。接下來的 T 行每行有三個 32 位元的有號整數。

## 輸出說明

對於每筆測資請輸出一行，其格式為：Case {x}: {triangle type}。其中 x 表示測資編號，{triangle type} 為三角形的種類。依三邊長的值，{triangle type} 是以下的一種： 

- Invalid - 這三邊無法形成一個三角形 
- Equilateral  -  三邊均等長
- Isosceles  - 恰有兩邊等長
- Scalene - 三邊均不等長

## 範例輸入 #1

```
4
1 2 5
1 1 1
4 4 2
3 4 5
```

## 範例輸出 #1

```
Case 1: Invalid
Case 2: Equilateral
Case 3: Isosceles
Case 4: Scalene
```
