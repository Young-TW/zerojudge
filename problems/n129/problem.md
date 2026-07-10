# n129. p1. 鋪磁磚問題

## 內容

給定一個長度為 $1\times n$ 的地板空間，你可以用許多 $1\times 1$、$1\times 2$、或 $1\times 3$ 大小的磁磚去鋪它。想請你寫一程式去計算共有幾種鋪法。下圖是一個長度為 $1\times 4$ 的地板：$$\huge\boxed{\color{white}A\vphantom{AC}}\!\!\;\boxed{\color{white}A\vphantom{AC}}\!\!\;\boxed{\color{white}A\vphantom{AC}}\!\!\;\boxed{\color{white}A\vphantom{AC}}$$


　　它一共有 $7$ 種鋪法，如下所示：


$$\huge\boxed{A\vphantom{AC}}\!\!\;\boxed{A\vphantom{AC}}\!\!\;\boxed{A\vphantom{AC}}\!\!\;\boxed{A\vphantom{AC}}$$ $$\huge\boxed{A\vphantom{AC}}\!\!\;\boxed{A\vphantom{AC}}\!\!\;\boxed{\ \ B\ \ \,\vphantom{AC}}$$ $$\huge\boxed{\ \ B\ \ \,\vphantom{AC}}\!\!\;\boxed{\ \ B\ \ \,\vphantom{AC}}$$ $$\huge\boxed{A\vphantom{AC}}\!\!\;\boxed{\ \ B\ \ \,\vphantom{AC}}\!\!\;\boxed{A\vphantom{AC}}$$ $$\huge\boxed{\ \ B\ \ \,\vphantom{AC}}\!\!\;\boxed{A\vphantom{AC}}\!\!\;\boxed{A\vphantom{AC}}$$ $$\huge\boxed{A\vphantom{AC}}\!\!\;\boxed{\quad\!\;C\quad\ \vphantom{AC}}$$ $$\huge\boxed{\quad\!\;C\quad\ \vphantom{AC}}\!\!\;\boxed{A\vphantom{AC}}$$


　　其中 $A$ 磁磚 $\huge\boxed{A\vphantom{AC}}$、$B$ 磁磚 $\huge\boxed{\ \ B\ \ \,\vphantom{AC}}$、及 $C$ 磁磚 $\huge\boxed{\quad\!\;C\quad\ \vphantom{AC}}$，分別表示 $1\times 1$、$1\times 2$、及 $1\times 3$ 大小的磁磚。

## 輸入說明

每筆測試資料只有一個正整數 $n$，$1\leq n\leq 71$，代表地板空間是 $1\times n$。

## 輸出說明

每筆測試資料的輸出只有一個正整數，表示共有幾種鋪法。

## 範例輸入 #1

```
4
```

## 範例輸出 #1

```
7
```

## 範例輸入 #2

```
5
```

## 範例輸出 #2

```
13
```
