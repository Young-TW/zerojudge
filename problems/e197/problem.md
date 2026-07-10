# e197. 倒回收

## 內容

時間堆起了塵埃 人海之中習慣混亂
不用感到困難 改變本來不簡單
教室走廊黑板 我曾讓它一塵不染
時間堆起了塵埃 人來人往髒亂太快
這麼做太不該 這生活需要我的愛
別囉嗦 別囉嗦 一起走
......


 


　　板橋高中在某年開始，打掃時間一到，名為「Clean up」的打掃歌就會響起，學生們就會知道需要打掃了。


　　這次，所有倒回收的$\color{black}{\space N\space}$個學生們集結了起來，討論了起來，如果假設每個人可以無延遲的拿到任何一個回收籃，且在每個人一趟最多只能拿兩個回收籃的情況下，要如何最高效的把回收倒完呢？


　　板橋高中倒回收的地點非常地擁擠，已知所有$\color{black}{\space M\space}$種回收的分類都排成一直線，且每一種回收距離回收場入口的距離是$\color{black}{\space d_1\sim d_M\space}$，假設一次只能有一個人進去把手上的回收倒完，出來之後另一個人才能進去，那一個進去的人手上若拿著兩種回收籃分別是$\color{black}{\space a,b\space}$，則他需要走$\color{black}{\space \max(d_a,d_b)\times 2\space}$的距離才有可能把回收倒完(走過去到最遠的那桶再走回來，中途遇到另一桶就可以倒了另一籃了)。


　　現在有很多籃回收籃(見輸入說明)要分給這$\color{black}{\space N\space}$個學生倒，假設每個學生走路速度一樣，請問在最佳的分配下(每個人可以不只倒一次回收)，學生們最少需要走的總距離和(等價於最佳效率)為多少？

## 輸入說明

輸入首行有一個正整數$\color{black}{\space T(T\leq 10)\space}$，代表測資筆數。


每筆測資首行有兩個正整數$\color{black}{\space N,M(N\leq 1000,M\leq 10^5))\space}$如題目所述。


接下來一行有$\color{black}{\space M\space}$個兩兩相異的正整數$\color{black}{\space d_1\sim d_M(d_i\leq 10^9)\space}$以空格隔開。


最後一行有$\color{black}{\space M\space}$個正整數$\color{black}{\space c_1\sim c_M(1\leq c_i\leq 10^4)\space}$，代表第$\color{black}{\space i\space}$種回收的回收籃共有$\color{black}{\space c_i\space}$籃。

## 輸出說明

輸出學生們最少需要走的總距離和為多少。

## 範例輸入 #1

```
2
3 3
3 2 1
2 2 2
1 5
1 5 4 3 2
2 1 1 1 2
```

## 範例輸出 #1

```
12
22
```
