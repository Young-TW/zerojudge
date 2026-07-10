# c533. 趙哥追妹子

## 內容

趙哥平常相當喜歡走在路上找尋可愛的萌妹子，村中的萌妹子們都相當害怕，所以他們串通好，如果今日趙哥突然在路上發作想要做出危險舉動時，住在當地妹子就會開始將訊息散布給其他住在周圍的萌妹子們，而周圍的萌妹子也會繼續散布消息，她們發現趙哥不會重複走已經走過的路，因此沒有必要將消息散布給趙哥已經經過或者不可能經過的萌妹子，以免造成不必要的緊張。已知趙哥所住的村莊有$\color{black}{\space n\space}$個萌妹子家及$\color{black}{\space n-1\space}$條道路，且從任意一個萌妹子家皆有道路可以到其他所有的萌妹子家，給你趙哥出發的地點以及趙哥發作的地點，請問有幾個妹子會知道這次趙哥發作的事情？

## 輸入說明

本題為單筆輸入
第一行有三個正整數$\color{black}{\space n,m,r\space}$，代表有$\color{black}{\space n\space}$個萌妹子家、$\color{black}{\space m\space}$個詢問以及趙哥出發的地點$\color{black}{\space r\space}$
接下來$\color{black}{\space n-1\space}$行，每行有兩個正整數$\color{black}{\space a,b\space}$，表示有一條道路連接$\color{black}{\space a\space}$號的萌妹子家跟$\color{black}{\space b\space}$號的萌妹子家 (萌妹子家的編號從$\color{black}{\space 1\space}$到$\color{black}{\space n\space}$)
再接下來$\color{black}{\space m\space}$行，每行有一個$\color{black}{\space q\space}$，代表趙哥發作的地點


對於所有測資$\color{black}{\space 0<m \leq n \leq 10^6,1 \leq r \leq n\space}$

## 輸出說明

對於每個詢問，請輸出一個正整數$\color{black}{\space k\space}$，代表有幾個妹子知道趙哥發作的消息

## 範例輸入 #1

```
8 2 8
7 2
1 7
4 2
4 5
6 2
7 3
4 8
2
6
```

## 範例輸出 #1

```
5
1
```
