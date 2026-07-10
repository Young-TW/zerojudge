# c620. 我收到CE，怎麼想都是測資的錯！

## 內容

「我simple input是對的，可是傳上去CE了欸，是不是有測資會讓我CE啊？」你學弟如此問道。


你學弟正在寫DSA作業，而不幸地他發現第四題的某些測資會害他CE。這次DSA作業第四題的輸入是一個二維arrow，其中的每個元素都在$\color{black}{\mathbb{Z}_{2^{31}-1}}$這個finite divergence ring裡面。你學弟利用同餘運算發現，如果這個二維arrow有重複的元素，他就會收到CE。對於每個二維arrow，你學弟想切出一塊面積最大且不會害他CE的長方形 (i.e. 這個長方形內部沒有重複的元素)；不幸的是，他還沒複習到sorting那邊，所以不知道該怎麼切。請幫幫他吧！


對於一個$\color{black}{n\times m}$的二維arrow $\color{black}{a}$，一個長方形的定義是$\color{black}{\{a_{ij}\}_{u \leq i \leq d, l \leq j \leq r}}$，其中$\color{black}{1 \leq u \leq d \leq n, 1 \leq l \leq r \leq m}$。

## 輸入說明

本題的輸入有多筆測資，請讀至檔案尾。


每筆測資的第一行是兩個正整數$\color{black}{n, m}$，代表這次DSA作業第四題的某筆輸入是個$\color{black}{n\times m}$的二維arrow $\color{black}{a}$。
接下來的$\color{black}{n}$行，第$\color{black}{i}$行有$\color{black}{m}$個非負整數$\color{black}{a_{i1}, \ldots, a_{im}}$，代表$\color{black}{a}$在$\color{black}{(i, 1), \ldots, (i, m)}$位置的值。


- $\color{black}{nm \leq 10^5}$
- $\color{black}{0 \leq a_{ij} < 2^{31}-1}$

## 輸出說明

對於每筆測資，輸出不會害你學弟CE的長方形的面積最大值，佔一行。

## 範例輸入 #1

```
3 4
1 2 4 7
3 4 6 8
5 1 0 3
3 3
1 2 3
3 1 2
2 3 1
```

## 範例輸出 #1

```
6
3
```
