# h625. 超級家教 HEHE篇

## 內容

$\color{black}{\text{l}}\color{red}{\text{inmozhisong}}$找了他所有的家教學生來一起上課，還叫了$\color{black}{\text{W}}\color{red}{\text{aimai}}$去幫忙點外賣。


而他的其中三個家教學生：$\color{black}{\text{b}}\color{red}{\text{ecaido}}$、$\color{black}{\text{k}}\color{red}{\text{enkenken}}$、$\color{black}{\text{r}}\color{red}{\text{1cky}}$正在玩超人遊戲。


$\color{black}{\text{k}}\color{red}{\text{enkenken}}$：「$\color{black}{\text{b}}\color{red}{\text{ecaido}}$是窩的『超人』」。


$\color{black}{\text{r}}\color{red}{\text{1cky}}$：「$\color{black}{\text{k}}\color{red}{\text{enkenken}}$是窩的『超人』」。


$\color{black}{\text{r}}\color{red}{\text{1cky}}$：「$\color{black}{\text{b}}\color{red}{\text{ecaido}}$是窩的『超級賽亞人』」。


這三人複雜的關係讓他的另外一位家教學生$\color{black}{\text{P}}\color{red}{\text{enguin07}}$感到很頭痛。


這時候，他最笨的家教學生$\color{gray}{\text{Ststone}}$突然笑了說：「hehe」。


$\color{black}{\text{l}}\color{red}{\text{inmozhisong}}$覺得很有趣，於是把他們三人的關係稱作HEHE關係（Hentai mEn's Hehe rElationship ）。


超電的$\color{black}{\text{l}}\color{red}{\text{inmozhisong}}$看到之後，決定把他的$N$個家教學生（沒錯他還是這麼電）全部找來一起玩超人遊戲，並且觀察他們之間有沒有HEHE關係。


為了簡化問題，他把他的家教學生編號成$1$到$N$，並且告訴每個人有哪些人是他的「超人」，其中，對於編號$i$的學生，他的「超人」們一定都會落在編號$1$到$i-1$。


就這麼分完了之後，$\color{black}{\text{l}}\color{red}{\text{inmozhisong}}$發現他居然忘記還有「超級賽亞人」了。


不過聰明的$\color{black}{\text{l}}\color{red}{\text{inmozhisong}}$馬上就想到了一個解決辦法，並告訴所有人：「若編號$j$的學生是編號$i$的學生的「超人」，且編號$j$的學生不是編號$i+1$到$n$的學生中任何一個人的「超人」了，那編號$j$的學生就是編號$i$的學生的「超級賽亞人」。


給你$\color{black}{\text{l}}\color{red}{\text{inmozhisong}}$分配好的關於$N$個學生的「超人」名單，請問在這份名單中可以看出有多少的HEHE關係存在呢？

## 輸入說明

輸入的第一行包含一個正整數$N$，代表$\color{black}{\text{l}}\color{red}{\text{inmozhisong}}$有$N$個家教學生。


接著有$N$行，每行包含($M_{i}+1$)個正整數$M_{i},a_{(i,1)},a_{(i,2)},...,a_{(i,M_{i})}$，代表名單中編號$a_{(i,1)},a_{(i,2)},...,a_{(i,M_{i})}$的人都是編號$i$的人的超人。


$1 \leq N \leq 10^5$


$0 \leq M_i \leq i-1$


$\sum M_i \leq 10^6$


$1 \leq a_{(i,j)} \leq i-1$

## 輸出說明

輸出一個正整數，代表共有多少的HEHE關係。

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
