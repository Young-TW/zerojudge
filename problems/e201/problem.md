# e201. 期末打掃

## 內容

每到了學期末，學生們總是需要打掃自己的教室，而身為檢查人員，最頭痛的就是去檢查了學生卻還沒打掃好，而剛好小明又是一個很懶惰的檢查員，所以小明不希望他需要走任何多餘的路線。
　　已知教室的分佈恰好是一棵圖論上的樹，即總共有$\color{black}{\space N\space}$間教室，且有$\color{black}{\space N-1\space}$條有長度的道路連結著這些教室，滿足任兩間教室都有一條唯一的簡單路徑可以互通。
　　小明所在的教室為$\color{black}{\space 1\space}$號，除此之外，小明向其他$\color{black}{\space N-1\space}$間教室的學生們宣告了截止時間，每間教室的截止時間是根據他們各自的整潔和秩序成績評比出來的，所以小明只要在某間教室的截止時間後檢查該間教室一次，不論他們有沒有打掃完，小明就可以不用再理這間教室了。
　　而，因為小明不希望他需要走任何多餘的路線，他也不想要把自己身上的東西揹在身上走，所以檢查完一遍所有教室後他也得回到$\color{black}{\space 1\space}$號教室拿東西，所以很顯然的他能走的路線長就只有「兩倍所有邊的長度和」這麼多而已。
　　於是，當他打算檢查某一間教室時，若該間教室的截止時間還沒到，他就得待在原地等到截止時間到了才可以檢查。
　　小明除了以上要求之外，他還希望他能盡可能地早點離開(越早檢查完所有教室後回到$\color{black}{\space 1\space}$號教室越好)，你能夠寫一支程式，在知道每間教室的截止時間和分佈圖後，告訴他他最早能夠在哪個時間點檢查完所有教室後回到$\color{black}{\space 1\space}$號教室嗎？
　　為了簡化問題，我們假設小明走了長度$\color{black}{\space x\space}$就得花費$\color{black}{\space x\space}$個時間點，且一開始小明在$\color{black}{\space 1\space}$號教室時的時間點為$\color{black}{\space 0\space}$，此外我們將假設檢查不需要花費任何時間。

## 輸入說明

輸入首行有一個正整數$\color{black}{\space T(T\leq 20)\space}$，代表測資筆數。


每筆測資首行有一個正整數$\color{black}{\space N(N\leq 5\times 10^4)\space}$，代表教室數量。


次行有$\color{black}{\space N-1\space}$個正整數$\color{black}{\space d_2\sim d_N(d_i\leq 10^9)\space}$，$\color{black}{\space d_i\space}$代表第$\color{black}{\space i\space}$間教室的截止時間點。


接下來$\color{black}{\space N-1\space}$行，每行三個正整數$\color{black}{\space a,b,w(1\leq a,b\leq N,w\leq 10^4)\space}$，代表有一條長度為$\color{black}{\space w\space}$的道路連結著$\color{black}{\space a\space}$號教室和$\color{black}{\space b\space}$號教室。保證給定的圖為一棵樹。

## 輸出說明

輸出小明從$\color{black}{\space 1\space}$號教室出發後，最早能夠在哪個時間點檢查完所有教室後回到$\color{black}{\space 1\space}$號教室。

## 範例輸入 #1

```
3
5
7 3 5 1
1 2 1
1 3 1
1 4 1
1 5 1
5
11 5 8 2
1 2 1
1 3 1
1 4 1
1 5 1
3
1 2
1 2 1
2 3 1
```

## 範例輸出 #1

```
8
12
4
```
