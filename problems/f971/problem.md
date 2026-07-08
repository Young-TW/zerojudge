# f971. WandaVision轉圈圈

## 內容

有一天 $\text{Wanda}$ 問了 $\text{Vision}$ 數學問題


$\text{Wanda}$：「$x^2=1,\ x=?$」


$\text{Vision}$：「等於 $1$ 或 $-1$ 」


$\text{Wanda}$：「那如果 $x^4=1,\ x=?$」


$\text{Vision}$：「等於 $1$ 或 $-1$ 或是 $i$ 或是 $-i$」


$\text{Wanda}$：「什麼是 $i$ ? 」


$\text{Vision}$：「$i$ 就是 $-1$ 開根號啊!」


$\text{Wanda}$：「好奇怪喔，這個世界是不是怪怪的? 」


$\text{Agatha}$：「竟然被你發現了，所以你現在要解出我的問題才能逃出去! 」


$\text{Wanda}$：「蛤?! 」


$\text{Agatha}$：「$x^n=1$ ，請輸出 $n$ 個 $x$ 的值。」


$\text{Wanda}$：「為什麼我都聽不懂這些問題，好難喔! 」


$\text{Vision}$：「$\text{Wanda}$ 我知道你為什麼都聽不懂」


$\text{Wanda}$：「為什麼? 」



![image](ShowImage?id=1785)


$\text{Vision}$：「看來你要多讀點書了。」


$\text{Wanda}$：「那我來讀黑暗神書。」

## 輸入說明

多筆輸入(不多於 $ \color{black}{1000}\ $ 筆)


每行輸入整數 $ \color{black}{n}\ $


代表 $ \color{black}{x^n=1}\ $ 的 $ \color{black}{n}\ $


- $ \color{black}{1≤n≤1000}\ $
- 每行的 $ \color{black}{n}\ $ 皆相異

## 輸出說明

對於每筆輸入，輸出 $ \color{black}{n}\ $ 個 $ \color{black}{a,\ b}\ $


代表 $ \color{black}{a+bi}\ $ 為其中一根


對於 $ \color{black}{a}\ $ 由小到大輸出，若 $ \color{black}{a}\ $ 相同，對於 $ \color{black}{b}\ $ 由小到大輸出


四捨五入到小數第 $ \color{black}{3}\ $ 位 (請先排序後再四捨五入輸出！)


$ \color{black}{Ex：}\ $


- $ \color{black}{12.3445→ 12.345，12.3444→ 12.344}\ $
$\color{black}{0.0005→ 0.001，0.0004→ 0.000}\ $
$\color{black}{-12.3445→ -12.345，-12.3444→ -12.344}\ $
$\color{black}{-0.0005→ -0.001，-0.0004→ 0.000}\ $

## 範例輸入 #1

```
1
2
3
4
```

## 範例輸出 #1

```
1.000 0.000
-1.000 0.000
1.000 0.000
-0.500 -0.866
-0.500 0.866
1.000 0.000
-1.000 0.000
0.000 -1.000
0.000 1.000
1.000 0.000
```
