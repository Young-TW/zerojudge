# p013. Fibonacci's computation process (DFS)

## 內容

費氏數列（Fibonacci Sequence）, 又稱為黃金分割數列。


$f(5)\left\{\begin{array}{left} f(4)\left\{\begin{array}{left} f(3)\left\{\begin{array}{left} f(2)\left\{\begin{array}{left} f(1) \\ f(0) \\  \end{array}\right. \\ f(1) \\  \end{array}\right. \\ f(2)\left\{\begin{array}{left} f(1) \\ f(0) \\  \end{array}\right. \\  \end{array}\right. \\ f(3)\left\{\begin{array}{left} f(2)\left\{\begin{array}{left} f(1) \\ f(0) \\  \end{array}\right. \\ f(1) \\  \end{array}\right. \\  \end{array}\right.$


在數學上，斐波那契數列是以遞歸的方法來定義：


𝑓0 = 0
𝑓1 = 1
𝑓𝑛 = 𝑓𝑛-1 + 𝑓𝑛-2 (𝑛 ≥ 2)


用白話文來說，就是費氏數列由 0 和 1 開始，之後的費波那契數就是由之前的兩數相加而得出。


現在，麻煩大家還原一下費氏數列的計算過程。

## 輸入說明

輸入含有一個正整數 𝑛 (1 ≤ 𝑛 ≤ 15)。

## 輸出說明

請參考範例輸出，從 𝑓𝑛 開始，模擬題敘的費氏數列計算過程。最後再輸出 𝑓𝑛 的值。


計算過程中的每兩個項目間以一個空白隔開。


本題採「寬鬆比對」，也就是每列前後的空白數量不影響評分。

## 範例輸入 #1

```
1
```

## 範例輸出 #1

```
f(1)
f(1) = 1
```

## 範例輸入 #2

```
3
```

## 範例輸出 #2

```
f(3) f(2) f(1)
          f(0)
     f(1)
f(3) = 2
```

## 範例輸入 #3

```
5
```

## 範例輸出 #3

```
f(5) f(4) f(3) f(2) f(1)
                    f(0)
               f(1)
          f(2) f(1)
               f(0)
     f(3) f(2) f(1)
               f(0)
          f(1)
f(5) = 5
```
