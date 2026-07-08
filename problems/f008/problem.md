# f008. 怕累的我，把力氣點滿就對了

## 內容

「身為一個法師，當然先升力氣啊！沒有力氣要怎麼唸咒語啊？」四千如是說。


沒錯，唸咒語施展小型魔法也是需要力氣的，而畫魔法陣施展大型魔法就更不用說了。四千最近讀了《魔法熱力學導論》，發現要施展威力為 $\color{black}{n}$ 的大爆射魔法，必須先在地上畫出 $\color{black}{n\times n}$ 的網格魔法陣，再唸特定的咒語才能完成。更精確地說，威力為 $\color{black}{n}$ 的大爆射魔法陣由 $\color{black}{n+1}$ 條水平線段與 $\color{black}{n+1}$ 條垂直線段構成，其中水平線段由 $\color{black}{\left\{\overline{(0, k), (n, k)}\right\}_{k=0}^n}$ 給出，垂直線段由 $\color{black}{\left\{\overline{(k, 0), (k, n)}\right\}_{k=0}^n}$ 給出。


怕累而不想親自動手畫魔法陣的四千，回想起以前學過的某個符文，在詠唱後地上會浮現一個正方形墨跡，而墨跡可以重疊。每次詠唱時四千可以指定正方形的左下角座標 $\color{black}{(x, y)}$ 與邊長 $\color{black}{r}$，畫出由 $\color{black}{(x, y), (x+r, y), (x+r, y+r), (x, y+r)}$ 這四個頂點形成的正方形。四千想透過多次詠唱這個符文來完成威力為 $\color{black}{n}$ 的大爆射魔法陣，但不幸的是他發現完成魔法陣的方法不只一種，符文詠唱次數也可能不同！例如當 $\color{black}{n=2}$ 時，可以依序詠唱 $\color{black}{(x, y, r) = (0, 0, 1), (0, 1, 1), (1, 0, 1), (1, 1, 1)}$，這樣總共需要詠唱 $\color{black}{4}$ 次符文；另外，也可以依序詠唱 $\color{black}{(x, y, r) = (0, 0, 1), (0, 0, 2), (1, 1, 1)}$，這樣總共只需要詠唱 $\color{black}{3}$ 次符文。


給定魔法陣的威力 $\color{black}{n}$，請幫怕累的四千找出一個次數最少的符文詠唱順序。注意畫完的圖形必須恰為威力為 $\color{black}{n}$ 的魔法陣，例如當 $\color{black}{n=2}$ 且 $\color{black}{(x, y, r) = (0, 0, 1), (0, 0, 2), (1, 1, 2)}$ 時，儘管魔法陣被最後的墨跡包含，仍然不是一個合法的符文詠唱。

## 輸入說明

輸入的第一行是一個正整數 $\color{black}{T}$，代表總共有幾筆測試資料。


每筆測試資料佔一行，由一個正整數 $\color{black}{n}$ 組成，代表大爆射魔法陣的威力。


- $\color{black}{1 \leq T \leq 20}$
- $\color{black}{1 \leq n \leq 2000}$

## 輸出說明

對於每筆測試資料，先輸出一行，恰包含一個正整數 $\color{black}{m}$，代表四千完成魔法陣需要的最少符文詠唱次數。


接下來請輸出 $\color{black}{m}$ 行，第 $\color{black}{i}$ 行恰包含三個以一空白隔開的非負整數 $\color{black}{x_i, y_i, r_i}$，代表第 $\color{black}{i}$ 次詠唱的正方形左下角座標為 $\color{black}{(x_i, y_i)}$ 而邊長為 $\color{black}{r_i}$。如果有多個次數最少的詠唱順序，請輸出任一個。


本題為 special judge，你的輸出會由出題者的程式判斷是否正確，程序如下：


- 如果你的 $\color{black}{m}$ 沒辦法被 parse 成 $\color{black}{2^{31}-1}$ 內的非負整數，你會收到 WA ("Fail to parse your minimum number of spells.")。
- 如果你的 $\color{black}{m}$ 錯誤，你會收到 WA ("Your minimum number of spells is incorrect.")。
- 如果你在接下來的 $\color{black}{m}$ 行，有任何一行沒辦法被 parse 成三個以一空白隔開的 $\color{black}{2^{31}-1}$ 內的非負整數，你會收到 WA ("Fail to parse your spells.")。
- 如果你的符文詠唱畫出來的東西不是威力為 $\color{black}{n}$ 的魔法陣，你會收到 WA ("Your mahojin is incorrect.")。

## 範例輸入 #1

```
2
2
3
```

## 範例輸出 #1

```
3
0 0 1
0 0 2
1 1 1
4
0 0 2
0 1 2
1 0 2
1 1 2
```
