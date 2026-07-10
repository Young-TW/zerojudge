# c698. 整數溢位問題

## 內容

對於一個 $\color{black}{m}$ 位元的有號整數，其能儲存的數字範圍為 $\color{black}{[-2^{m-1},\ 2^{m-1})}$ ，當運算過程超出這個範圍，就會產生溢位，這時記憶體儲存的數值可能無法預期。


下圖兩軸 $\color{black}{x,\ y}$ 為 8 位元有號整數，以黑色繪製出相乘發生溢位的位置。



![image](ShowImage?id=1301)


現在問題來了，在給定的範圍 $\color{black}{[l,\ r]}$ 中，有多少數對 $\color{black}{(p, q)}$ 滿足 $\color{black}{p,\ q}$ 在 $\color{black}{m}$ 位元下相乘會發生溢位？

## 輸入說明

首行有一正整數 $\color{black}{T \le 100}$ 代表測資筆數。


接下來 $\color{black}{T}$ 行，每行有三個整數 $\color{black}{m, l, r}$ 以空格隔開，其中 $\color{black}{2 \le m \le 32\text{ 且}-2^{m - 1} \le l \le r < 2^{m - 1}}$ (意即 $\color{black}{l, r}$ 為合法的 $\color{black}{m}$ 位元有號整數)。

## 輸出說明

$\color{black}{p * q\ (l \le p,\ q \le r)}$ 溢位的數對總數

## 範例輸入 #1

```
1
2 -2 1
```

## 範例輸出 #1

```
3
```
