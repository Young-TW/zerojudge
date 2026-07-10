# b494. 史蒂芙的修羅道

## 內容

背景
史蒂芙被王國政務工作忙昏頭，每次都要求效率的極限，即使不會玩遊戲，只要把政務工作處理到極致，想必這就是另一種人生價值。


題目描述 
回顧一個經典問題區間極大極小值詢問 RMQ，她收到下面這一份代碼



```
#include 
using namespace std;

unsigned int seed = 0;
unsigned int p_random() {return seed = (seed*9301+49297);}

unsigned int A[5000005];
int main() {
	int N, M, S, x, y;
	unsigned int hash = 0;
	scanf("%d %d %d", &N, &M, &S);
	seed = S;
	for (int i = 1; i  y)	swap(x, y);
		unsigned int max_val = A[x];
		for (int j = x; j 「給定 $N$ 個整數、$M$ 個詢問操作、$S$ 為亂數種子，接著產生 $N$ 個數字，對於接下來 $M$ 個詢問，每一個詢問兩個整數，輸出區間內的最大值。」這對曾經的史蒂芙而言，用過 Segment Tree、Sparse Table、Unrolled Linked List 解決過，時間、空間複雜度都非常優秀。


現在的工作就是加速這一份代碼。

## 輸入說明

只有一組測資，每一組測資只包含三個整數 $N, \; M, \; S$。


- $ 1 \le N, M \le 5000000$
- $0 \le S \le 2147483647$

## 輸出說明

對於每組測資輸出一行一個整數。

## 範例輸入 #1

```
8 5 10
```

## 範例輸出 #1

```
4049919279
```
