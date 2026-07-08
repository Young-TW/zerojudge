# e447. queue 練習

## 內容

請你實作queue相關的幾個基本操作：


- 在隊伍尾端加入元素。
- 輸出隊伍最前端的元素。
- 刪除隊伍最前端的元素。

## 輸入說明

第一行有一個$\space\color{black}{N(1\leq N\leq 10^5)\space}$，接下來有$\space\color{black}{N}\space$行，每一行一開始有一個$\space\color{black}{k}\space$，代表哪一種操作：


- 如果$\space\color{black}{k=1}\space$，請再讀入一個整數$\space\color{black}{x(1\leq x\leq 10^9)}\space$，並在隊伍尾端加入該整數。
- 如果$\space\color{black}{k=2}\space$，請輸出隊伍最前端的元素，如果當前隊伍內沒有元素，請輸出$\space\color{black}{-1}\space$。
- 如果$\space\color{black}{k=3}\space$，請刪除隊伍最前端的元素，如果當前隊伍內沒有元素，請無視該操作。

## 輸出說明

對於每次$\space\color{black}{k=2}\space$操作，輸出一個整數於一行，代表當時隊伍最前端的元素，如果當時隊伍內沒有元素，請輸出$\space\color{black}{-1}\space$。

## 範例輸入 #1

```
13
1 1
1 2
1 3
2
3
3
2
1 4
3
2
3
3
2
```

## 範例輸出 #1

```
1
3
4
-1
```
