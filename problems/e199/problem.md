# e199. 資訊社的羈絆

## 內容

資訊社一家親，為了加強歷屆所有資訊社社員的羈絆，我們希望能不斷加強人與人之間的關係。


　　為此，你需要在已知的$\color{black}{\space N\space}$個人(編號$\color{black}{\space 1\sim N\space}$)之間不斷進行以下兩種操作：


　　1. $\color{black}{\space add\;a\;b\space}$：加強編號$\color{black}{\space a\space}$和$\color{black}{\space b\space}$的關係，好讓資訊社的羈絆更穩固。


　　2. $\color{black}{\space query\space}$：詢問有多少人$\color{black}{\space x\space}$滿足「存在一對$\color{black}{\space a,b\space}$，無論怎麼沿著人與人之間加強的關係走，都一定得經過$\color{black}{\space x\space}$才能從一方抵達另一方」。也就是當這個人消失，$\color{black}{\space a,b\space}$之間的間接強烈關係就會從原本存在變成斷開，這樣我們可能就得把$\color{black}{\space x\space}$列入觀察名單之中，為了方便起見，請你再由小到大把這些人的編號輸出出來。


　　奮鬥吧！

## 輸入說明

輸入首行有一個正整數$\color{black}{\space T(T\leq10)\space}$代表測資筆數。


每筆測資首行有兩個正整數$\color{black}{\space N,Q(N\leq600,Q\leq180300)\space}$，代表要加強關係的資訊社人數和操作次數，其中操作滿足$\color{black}{\space add\space}$操作不會重複加強同樣的兩個人的關係；$\color{black}{\space query\space}$操作不超過$\color{black}{\space 600\space}$次。


接下來$\color{black}{\space Q\space}$行，每行一種操作。

## 輸出說明

對於每個$\color{black}{\space query\space}$操作，輸出一行，第一個數字$\color{black}{\space k\space}$代表滿足條件的人數，接下來由小到大輸出$\color{black}{\space k\space}$個數字代表滿足條件人們的編號。同一行的所有數字之間以空格隔開。

## 範例輸入 #1

```
1
4 8
add 1 2
query
add 2 3
query
add 3 4
query
add 4 1
query
```

## 範例輸出 #1

```
0
1 2
2 2 3
0
```
