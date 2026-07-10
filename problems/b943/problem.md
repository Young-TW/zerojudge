# b943. 複數 の 指對數

## 內容

複數可以表示成$\color{black}{\space a+b\thinspace i\space}$的形式$\color{black}{\space(a,b\in\Bbb R)}$，
　如果把複數$\color{black}{\space a+b\thinspace i\space}$對應到座標平面上的點$\color{black}{\space(a,b)}$，
　可以發現複數與座標平面上的點有一對一的性質，
　因此在平面上的點$\color{black}{\space(a,b)}$可以代表複數$\color{black}{\space a+b\thinspace i\space}$，
　例如：點$\color{black}{\space(3,4)}$可以代表複數$\color{black}{\space 3+4\thinspace i\space}$。



　複數$\color{black}{\space z=a+b\thinspace i\space}$可對應至複數平面點$\color{black}{\space\small P\normalsize\thinspace(3,4)}$，
　令$\color{black}{\space\small\overline{OP}\normalsize=r\space}$且$\color{black}{\space\small\overline{OP}\normalsize\space}$為有向角$\color{black}{\space\theta\space}$的終邊，
　則$\color{black}{\space r=\small\sqrt{a^2+b^2}\normalsize,\space\theta=\arctan\big(\frac{b}{a}\big),\space a=r\thinspace\cos\theta,\space b=r\thinspace\sin\theta\space}$，
　因此$\color{black}{\space z=a+b\thinspace i=r\thinspace(\cos\theta+i\thinspace\sin\theta)\space}$。



　根據泰勒展開式可得，
　$\color{black}{e^x=\displaystyle\sum_{n=0}^{\infty}\frac{x^n}{n!}=1+x+\frac{x^2}{2!}+\frac{x^3}{3!}+\cdots}$
　$\color{black}{\sin x=\displaystyle\sum_{n=0}^{\infty}\frac{(-1)^nx^{2n+1}}{(2n+1)!}=x-\frac{x^3}{3!}+\frac{x^5}{5!}-\frac{x^7}{7!}+\cdots}$
　$\color{black}{\cos x=\displaystyle\sum_{n=0}^{\infty}\frac{(-1)^nx^{2n}}{(2n)!}=1-\frac{x^2}{2!}+\frac{x^4}{4!}-\frac{x^6}{6!}+\cdots}$
　所以，
　$\color{black}{e^{ix}=\displaystyle1+ix+\frac{(ix)^2}{2!}+\frac{(ix)^3}{3!}+\frac{(ix)^4}{4!}+\frac{(ix)^5}{5!}+\frac{(ix)^6}{6!}+\frac{(ix)^7}{7!}+\cdots}$
　$\color{transparent}{e^{ix}}\color{black}{=\displaystyle1+ix-\frac{x^2}{2!}-\frac{ix^3}{3!}+\frac{x^4}{4!}+\frac{ix^5}{5!}-\frac{x^6}{6!}-\frac{ix^7}{7!}+\cdots}$
　$\color{transparent}{e^{ix}}\color{black}{=\displaystyle\left(1-\frac{x^2}{2!}+\frac{x^4}{4!}-\frac{x^6}{6!}+\cdots\right)+\thinspace i\left(x-\frac{x^3}{3!}+\frac{x^5}{5!}-\frac{x^7}{7!}+\cdots\right)}$
　$\color{transparent}{e^{ix}}\color{black}{=\cos x+i\thinspace\sin x}$
　(這同時也是著名的歐拉恆等式的由來$\color{black}{\space e^{i\pi }+1=(\cos\pi+i\thinspace\sin\pi)+1=-1+0+1=0\space}$)
　故$\color{black}{\space z=a+b\thinspace i=r\thinspace(\cos\theta+i\thinspace\sin\theta)=re^{i\theta}=\small\sqrt{a^2+b^2}\normalsize\cdot e^{i\arctan\big(\large\frac{b}{a}\normalsize\big)}}$



　由上述的公式，
　我們可以對複數的指數進行定義：
　$\color{black}{(a+b\thinspace i)^{(c+d\hspace{2px}i)}=\Big(\small\sqrt{a^2+b^2}\normalsize\cdot e^{i\arctan\big(\frac{b}{a}\big)}\Big)^{(c+d\hspace{2px}i)}}$
　$\color{transparent}{(a+b\thinspace i)^{(c+d\hspace{2px}i)}}\color{black}{=\small\sqrt{a^2+b^2}^{\space(c+d\hspace{2px}i)}\normalsize\cdot e^{(c+d\hspace{2px}i)\hspace{1px}i\arctan\big(\frac{b}{a}\big)}}$
　$\color{transparent}{(a+b\thinspace i)^{(c+d\hspace{2px}i)}}\color{black}{=\small\sqrt{a^2+b^2}^{\space c}\normalsize\cdot\small\sqrt{a^2+b^2}^{\space d\hspace{1px}i}\normalsize\cdot e^{c\hspace{1.5px}i\arctan\big(\frac{b}{a}\big)-\hspace{1.5px}d\arctan\big(\frac{b}{a}\big)}}$
　$\color{transparent}{(a+b\thinspace i)^{(c+d\hspace{2px}i)}}\color{black}{=\small\sqrt{a^2+b^2}^{\space c}\normalsize\cdot e^{\space d\hspace{1px}i\ln(\sqrt{a^2+b^2}\space)}\cdot e^{c\hspace{1.5px}i\arctan\big(\frac{b}{a}\big)}\cdot e^{-d\arctan\big(\frac{b}{a}\big)}}$
　$\color{transparent}{(a+b\thinspace i)^{(c+d\hspace{2px}i)}}\color{black}{=\displaystyle\frac{\small\sqrt{a^2+b^2}^{\space c}\normalsize}{e^{d\arctan\big(\frac{b}{a}\big)}}\textstyle\cdot e^{i\left(\space d\ln(\sqrt{a^2+b^2}\space)+\hspace{1.5px}c\arctan\big(\frac{b}{a}\big)\right)}}$
　$\color{transparent}{(a+b\thinspace i)^{(c+d\hspace{2px}i)}}\color{black}{=\displaystyle\frac{\small\sqrt{a^2+b^2}^{\space c}\normalsize}{e^{d\arctan\big(\frac{b}{a}\big)}}\textstyle\cdot\left[\cos\Big(d\ln(\small\sqrt{a^2+b^2}\normalsize\space)+c\arctan\big(\frac{b}{a}\big)\Big)+i\sin\Big(d\ln(\small\sqrt{a^2+b^2}\normalsize\space)+c\arctan\big(\frac{b}{a}\big)\Big)\right]}$



　我們也可以對複數的對數進行定義：
　$\color{black}{\log_{(a+b\hspace{2px}i)}(c+d\thinspace i)=\displaystyle\frac{\ln(c+d\thinspace i)}{\ln(a+b\thinspace i)}}$
　$\color{transparent}{\log_{(a+b\hspace{2px}i)}(c+d\thinspace i)}\color{black}{=\displaystyle\frac{\ln\Big(\small\sqrt{c^2+d^2}\normalsize\cdot e^{i\arctan\big(\frac{d}{c}\big)}\Big)}{\ln\Big(\small\sqrt{a^2+b^2}\normalsize\cdot e^{i\arctan\big(\frac{b}{a}\big)}\Big)}}$
　$\color{transparent}{\log_{(a+b\hspace{2px}i)}(c+d\thinspace i)}\color{black}{=\displaystyle\frac{\ln(\small\sqrt{c^2+d^2}\normalsize)+i\arctan\big(\frac{d}{c}\big)}{\ln(\small\sqrt{a^2+b^2}\normalsize)+i\arctan\big(\frac{b}{a}\big)}\space}$(同複數除法$\color{black}{\frac{a+b\thinspace i}{c+d\thinspace i}=\frac{(a+b\thinspace i)(c-d\thinspace i)}{(c+d\thinspace i)(c-d\thinspace i)}=\frac{(ac+bd)+(bc-ad)\thinspace i}{c^2+d^2}}$)
　$\color{transparent}{\log_{(a+b\hspace{2px}i)}(c+d\thinspace i)}\color{black}{=\displaystyle\frac{\big(\ln(\small\sqrt{a^2+b^2}\normalsize)\ln(\small\sqrt{c^2+d^2}\normalsize)+\arctan\big(\frac{b}{a}\big)\arctan\big(\frac{d}{c}\big)\big)+\big(\ln(\small\sqrt{a^2+b^2}\normalsize)\arctan\big(\frac{d}{c}\big)-\ln(\small\sqrt{c^2+d^2}\normalsize)\arctan\big(\frac{b}{a}\big)\big)\thinspace i}{\ln^2(\small\sqrt{a^2+b^2}\normalsize)+\arctan^2\big(\frac{b}{a}\big)}}$

## 輸入說明

有多筆測資，每筆測資包含$\color{black}{\space3\space}$行。


第一行有$\color{black}{\space1\space}$個整數$\color{black}{\space K\space}$，代表操作指令，其中$\color{black}{\space K\space}$只可能是$\color{black}{\space0、1、2\space}$。
①當$\color{black}{\space K=1\space}$時，請操作以複數$\color{black}{\space z_1\space}$為底數，複數$\color{black}{\space z_2\space}$為指數的指數運算。
②當$\color{black}{\space K=2\space}$時，請操作以複數$\color{black}{\space z_1\space}$為底數，複數$\color{black}{\space z_2\space}$為真數的對數運算。
③當$\color{black}{\space K=0\space}$時，代表輸入結束，請不要對之後的數字做任何操作。


第二行有$\color{black}{\space2\space}$個實數$\color{black}{\space a、b\space}$，代表複數$\color{black}{\space z_1=a+b\thinspace i\space}$，
其中$\color{black}{\space-5\le a,b\le5\space}$。


第三行有$\color{black}{\space2\space}$個實數$\color{black}{\space c、d\space}$，代表複數$\color{black}{\space z_2=c+d\thinspace i\space}$，
其中$\color{black}{\space-5\le c,d\le5\space}$。

## 輸出說明

對於每筆測資請輸出一行，輸出請符合格式，並根據輸入進行計算後，依照下述條件輸出。


假設正確答案為複數$\color{black}{\space z_3=p+q\thinspace i\hspace{5px}}$：
請輸出$\color{black}{\space p\pm|q|i\space}$，請依$\color{black}{\space q\space}$的正負判斷運算子為$\color{black}{\space+\space}$或$\color{black}{\space-\space}$。
當$\color{black}{\space q=0\space}$時，請使用$\color{black}{\space+\space}$運算子。


對於輸出的所有數字，請四捨五入至小數點後$\color{black}{\space6\space}$位。
(相信我, 不看提示會後悔~~~ OωO )

## 範例輸入 #1

```
2
2 0
3 0
1
1 -1
2 0
1
1 3
3 0
2
-1 -1
-1 -1
0
1 2
2 3
1
0 1
1 0
```

## 範例輸出 #1

```
1.584963 + 0.000000i
0.000000 - 2.000000i
-26.000000 - 18.000000i
1.000000 + 0.000000i
```
