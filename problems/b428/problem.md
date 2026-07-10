# b428. 凱薩加密

## 內容

背景曾幾何時，基礎題庫已經成了不基礎的題庫。小小新手們寫個題目，不少拿了 TLE、CE 求助無門，就再也不想打開 Zerojudge。高中生哪有寫這麼困難的題目，高中生都不像高中生。在某 M 那個年代寫的題目非常簡單，沒有特別變化處理，更別說多麼高檔的資料結構，暴力算法 (naive algorithm) 就能輕鬆切題。

「年代變了呢，現在的高中生要寫出比大學生的某 M 更困難的題目」

重溫解題的那份初心吧！

題目描述 在西元前就存在的一種加密－凱薩加密為目前最早發現的替換加密 (substitution cipher)。其原理很簡單，將一段明文往替換成往後數的第 $k$ 個英文字母。

若用數學式表示凱薩加密和解密，如下：

加密 $C = E_K(P) = (P + k) \mod 26$
解密 $P = D_K(P) = (C - k) \mod 26$  

例如 $k = 3$ 時，發生的情況如下：

明文字母表：ABCDEFGHIJKLMNOPQRSTUVWXYZ 
密文字母表：DEFGHIJKLMNOPQRSTUVWXYZABC從數學的觀點來看，每一個字母就是一個數字。A = 0, B = 1, C = 2, ...,X = 23, Y = 24, Z = 25

## 輸入說明

多組測資，每一組測資兩行，分別是明文和經過凱薩加密的密文，保證明文和密文長度相同，長度小於等於 1000 大於 0 且只由大寫英文字母構成。

## 輸出說明

對於每組測資輸出一行，凱薩加密使用的 $k$ 值為何，其 $0 \le k < 26$

## 範例輸入 #1

```
ABCDEFGHIJKLMNOPQRSTUVWXYZ 
DEFGHIJKLMNOPQRSTUVWXYZABC
DLQXABXEEQMEUQYLZPEK
YGLSVWSZZLHZPLTGUKZF
Z
Z
```

## 範例輸出 #1

```
3
21
0
```
