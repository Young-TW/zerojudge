# b991. friunlde函數

## 內容

現在定義一個函數叫friunlde函數，以下是他的性質


friunlde(n,k)共有兩項變數n,k，n為非負整數，k為1或2


當n為奇數時，friunlde(n,k)=mex{friunlde(n-1,k)}


當n為偶數且非0時，friunlde(n,k)=mex{friunlde(n-1,k),friunlde(n/2,k)*(k%2)}


當n=0時，friunlde(n,k)=0


mex函數為最小沒有出現的非負整數，mex{1,2}=0,mex{0,3}=1;


現在給你n和k，要你求friunlde(n,k)的值，本題為EOF版

## 輸入說明

0<=n<=10^18,k=1or2

## 輸出說明

對於每組n,k求出friunlde(n,k)的值

## 範例輸入 #1

```
0 1
1 1
2 1
0 2
1 2
2 2
```

## 範例輸出 #1

```
0
1
0
0
1
2
```
