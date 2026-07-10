# c668. 下一個質數

## 內容

給您一個數字 n
請找出最接近 n 的質數 p
且 p > n

 本題無法以暴力 AC , 也無法利用建質數表來 AC , 請找出比較有效率的方法，
可參考
  米勒-拉賓質數判定法
  費馬小定理
  http://www.csie.ntnu.edu.tw/~u91029/Prime.html
  http://miller-rabin.appspot.com/

 
# python 的朋友，針對每行測資


s = sys.stdin.readline()
n = int(s)
k = n // 6 

while(1):
    p = k * 6 + 1 ## 每 6 個數，測試 2 個，且末位是 5 不必測試。
    q = k * 6 + 5
    if(p > n and p%5!=0 and isPrime(p)):
        print(p)
        break
    if(q > n and q%5!=0 and isPrime(q)):
        print(q)
        break
    k += 1

## 輸入說明

每個測資點的第一行有三個數字   T  min  max


表示有 T 個待測數字，待測數字的最小值 min ，最大值 max。


所有的數字 n 小於 232

## 範例輸入 #1

```
3 234 5543
234
2131
5543
```

## 範例輸出 #1

```
239
2137
5557
```
