# h624. 超級家教  YEE篇

## 內容

$\color{black}{\text{l}}\color{red}{\text{inmozhisong}}$有$N$個家教學生（沒錯他就是這麼電），$\color{black}{\text{h}}\color{red}{\text{a._.}}$是他的家教學生的其中之一，也是$\color{black}{\text{l}}\color{red}{\text{inmozhisong}}$的ㄋㄩˇㄆㄥˊㄧㄡˇ。


但是在$\color{black}{\text{l}}\color{red}{\text{inmozhisong}}$的學生裡面，存在著一種「抄抄抄」的風氣，常常會有人互相抄作業，使得$\color{black}{\text{l}}\color{red}{\text{inmozhisong}}$很不高興。


他發現抄的方式有分成兩種：「小抄」及「大抄」。


像是前幾天才被他抓到，$\color{black}{\text{k}}\color{red}{\text{enkenken}}$「大抄」了$\color{black}{\text{b}}\color{red}{\text{ecaido}}$的作業；$\color{black}{\text{r}}\color{red}{\text{1cky}}$「大抄」了$\color{black}{\text{k}}\color{red}{\text{enkenken}}$的作業；且$\color{black}{\text{r}}\color{red}{\text{1cky}}$也「小抄」了$\color{black}{\text{b}}\color{red}{\text{ecaido}}$的作業，$\color{black}{\text{l}}\color{red}{\text{inmozhisong}}$稱他們這樣的抄襲關係為YEE關係（Yokunai yEe rElationship ）。


他又發現他的學生們很奇怪，他可以以某種方式將他們編號成$1$到$N$，然後對於編號$i$的學生，他只會抄編號$1$到$i-1$的學生的作業。


聰明的$\color{black}{\text{l}}\color{red}{\text{inmozhisong}}$可以透過筆跡鑑定來找出哪些學生「小抄」了哪些學生的作業，但是「大抄」似乎就不好找了。


他研究了一番之後，發現了「大抄」的規則：若編號$i$的學生「小抄」了編號$j$的學生，且編號$1$到$i-1$的學生都沒有人「小抄」了編號$j$的學生，那編號$i$的學生就是「大抄」了編號$j$的學生。


給你$\color{black}{\text{l}}\color{red}{\text{inmozhisong}}$觀察筆跡後列出的「小抄」名單，請問在這份名單中可以看出有多少的YEE關係存在呢？

## 輸入說明

輸入的第一行包含一個正整數$N$，代表$\color{black}{\text{l}}\color{red}{\text{inmozhisong}}$有$N$個家教學生。


接著有$N$行，每行包含($M_{i}+1$)個正整數$M_{i},a_{(i,1)},a_{(i,2)},...,a_{(i,M_{i})}$，代表編號$i$的學生「小抄」了編號$a_{(i,1)},a_{(i,2)},...,a_{(i,M_{i})}$的學生的作業。


$1 \leq N \leq 10^5$


$0 \leq M_i \leq i-1$


$\sum M_i \leq 10^6$


$1 \leq a_{(i,j)} \leq i-1$

## 輸出說明

輸出一個正整數，代表共有多少的YEE關係。

## 範例輸入 #1

```
3
0
1 1
2 1 2
```

## 範例輸出 #1

```
1
```

## 範例輸入 #2

```
4
0
0
2 1 2
3 1 2 3
```

## 範例輸出 #2

```
2
```
