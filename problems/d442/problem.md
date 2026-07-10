# d442. 10591 - Happy Number

## 內容

讓我們定義正整數 S0 中每個數字的平方和為 S1。以相同的方法我們定義 S1 中每個數字的平方和為 S2，並依此類推。假如有某個 Si = 1（ i >= 1）則我們說 S0 是一個 Happy number。如果某一個數不是 Happy number，那他就是一個 Unhappy number。

例如： 7 是一個 Happy number，因為 7 -> 49 -> 97 ->130 -> 10 -> 1。

但是 4 是一個 Unhappy number，因為 4 -> 16 -> 37 -> 58 -> 89 -> 145 -> 42 -> 20 -> 4，永遠也無法產生  1。

## 輸入說明

輸入的第一列有一個整數代表以下有多少組測試資料

每組測試資料一列含有 1 個正整數 N（ N < 109）

## 輸出說明

對每組測試資料輸出一列

輸出 N 為 Happy number 或 Unhappy number

請參考 Sample Output

## 範例輸入 #1

```
3
7
4
13
```

## 範例輸出 #1

```
Case #1: 7 is a Happy number.
Case #2: 4 is an Unhappy number.
Case #3: 13 is a Happy number. 
```
