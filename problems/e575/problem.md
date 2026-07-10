# e575. 10908 - Largest Squares

## 內容

給定一個字元矩形，您必須找出最大正方形的邊的長度。
在其中正方形內的所有字元皆相同，並且正方形的中心(兩個對角線的交點)位於位置(r, c)。
矩形的高度和寬度分別為M和N。矩形的左上角座標為(0, 0)，右下角座標為(M-1, N-1)。


比方說下面給出的字元矩形。給定中心位置(1, 2)，此最大正方形邊長為3。


abbbaaaaaa
abbbaaaaaa
abbbaaaaaa
aaaaaaaaaa
aaaaaaaaaa
aaccaaaaaa
aaccaaaaaa

## 輸入說明

輸入第一行為一個整數T (T < 21)，T代表有幾組測資。
每組測資的第一行包含三個整數M，N (1 <= M, N <= 100)，Q (Q < 21)。
其中M，N表示矩形的高度和寬度，Q代表詢問的數量。
接下來M行每行N個字元，代表輸入的字元矩形。
接下來Q行，每行包含兩個整數r和c。

## 輸出說明

對於每組測資。
第一行輸出M，N，Q值，以空格分開。
接下來Q行，輸出以(r, c)當中心所對應的最大正方形邊長。

## 範例輸入 #1

```
1
7 10 4
abbbaaaaaa
abbbaaaaaa
abbbaaaaaa
aaaaaaaaaa
aaaaaaaaaa
aaccaaaaaa
aaccaaaaaa
1 2
2 4
4 6
5 2
```

## 範例輸出 #1

```
7 10 4
3
1
5
1
```
