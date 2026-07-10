# f446. 1237 - Expert Enough

## 內容

給你 n 筆資料，每筆告訴你工廠名、出產過車子最低和最高價格，
共有 q 組詢問，每組給你一個整數 p，
輸出出產車子價格區間包含 p 的工廠名，
如果有多間同時符合或沒有半間符合，輸出 UNDETERMINED


Auto-mobile Charting & Manufacturing (ACM) is a company that specializes in manufacturing automobile spare parts. Being one of the leading automotive companies in the world, ACM are sure to keep up the latest information in that world. In the 100-year anniversary of the company, ACM compiled a huge list of range of prices of any automobiles ever recorded in the history. ACM then wants to develop a program that they called Automobile Expert System or AES for short.


The program receives a price P as an input, and searches through the database for a car maker in which P falls in their range of lowest price L and highest price H of car they ever made. The program then output the car maker name. If the database contains no or more than one car maker that satisfies the query, the program produce output ‘UNDETERMINED’ (without quotes). Not so expert, huh? You are about to develop that program for ACM.

## 輸入說明

第一行有個T代表測資數(T<=10)
每筆測資的第一行有個D代表工廠數(D < 10000)
接下來D行每行分別有工廠名(不含空格)和價格區間L,R(0 < L < H < 1000000)
之後有個Q代表詢問數
接下來Q行每行有一個P代表詢問的車子價錢(0 < P < 1000000)


The input begins with a line containing an integer T (T ≤ 10), the number of test cases follow. Each case begins with the size of the database D (D < 10000). The next each of D lines contains M, L and H (0 < L < H < 1000000) which are the name of the maker (contains no whitespace and will never exceeds 20 characters), the car’s lowest price the maker ever made, and the car’s highest price the maker ever made respectively. Then there is the number of query Q (Q < 1000) follows. Each of the next Q lines contains an integer P (0 < P < 1000000), the query price.

## 輸出說明

如果知道是哪間工廠生產的就輸出該工廠名
否則輸出"UNDETERMINED"(不含雙引號)


Output for each query should be one line containing the name of the maker, or the string ‘UNDETERMINED’ (without quotes)

## 範例輸入 #1

```
1
4
HONDA 10000 45000
PEUGEOT 12000 44000
BMW 30000 75900
CHEVROLET 7000 37000
4
60000
7500
5000
10000
```

## 範例輸出 #1

```
BMW
CHEVROLET
UNDETERMINED
UNDETERMINED
```
