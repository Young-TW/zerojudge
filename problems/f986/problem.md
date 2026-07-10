# f986. Polynomial Queries

## 內容

Your task is to maintain an array of $\color{black}{n}\ $ values and efficiently process the following types of queries:


- Increase the first value in range $\color{black}{[\ a,b\ ]}\ $ by $\color{black}{1}\ $ , the second value by $\color{black}{2}\ $ , the third value by $\color{black}{3}\ $ , and so on.
- Calculate the sum of values in range $\color{black}{[\ a,b\ ]}\ $ .

你的任務是要對大小為 $\color{black}{n}\ $ 的陣列做下列的事：


- 將範圍在 $\color{black}{[\ a,b\ ]}\ $ 間的元素，第一個元素加 $\color{black}{1}\ $，第二個元素加 $\color{black}{2}\ $，第三個元素加 $\color{black}{3}\ $，依此類推。
- 計算在區間 $\color{black}{[\ a,b\ ]}\ $ 的元素總和。

## 輸入說明

The first input line has two integers $\color{black}{n}\ $ and $\color{black}{q}\ $ : the size of the array and the number of queries.

The next line has $\color{black}{n}\ $ values $\color{black}{t_1,t_2,...,t_n}\ $ : the initial contents of the array.

Finally, there are $\color{black}{q}\ $ lines describing the queries. The format of each line is either " $\color{black}{1\ a\ b}\ $ " or " $\color{black}{2\ a\ b}\ $ ".


第一行有兩個整數 $\color{black}{n}\ $ 和 $\color{black}{q}\ $ 代表陣列的大小和要詢問的次數。

下一行有 $\color{black}{n}\ $ 個數字 $\color{black}{t_1,t_2,...,t_n}\ $ 代表陣列的初始值。

最後有 $\color{black}{q}\ $ 行詢問。格式為 " $\color{black}{1\ a\ b}\ $ " 或 " $\color{black}{2\ a\ b}\ $ "，代表加值或是輸出總和。


- $\color{black}{1≤n,q≤2\times 10^5}\ $
- $\color{black}{1≤t_i≤10^6}\ $
- $\color{black}{1≤a≤b≤n}\ $

## 輸出說明

Print the answer to each sum query.


對於每次詢問總和時輸出總和。

## 範例輸入 #1

```
5 3
4 2 3 1 7
2 1 5
1 1 5
2 1 5
```

## 範例輸出 #1

```
17
32
```
