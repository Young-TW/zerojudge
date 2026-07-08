# f979. Purple Hills

## 內容

![image](ShowImage?id=1793)


"I've been so many places, I've seen so many faces.
But nothin' compares to these blue and yellow purple hills.
I've climbed the highest mountain once or twice, but who's countin'?
But nothin' compares to these blue and yellow purple hills."


只要爬到 Purple Hill 上面，眼前就會出現好多畫面


在第 n 號的 Purple Hill 上，出現的畫面數就有 1 + 2x + 3x^2 +...+ (n+1)x^n 個

## 輸入說明

每行輸入正整數 x 和 n


1≤ x ≤10^6，1≤ n <2^31

## 輸出說明

輸出總畫面數


因為答案可能會很大，請把答案 %1000000007 後再輸出

## 範例輸入 #1

```
1 1
1 2
1 3
2 1
2 2
2 3
12345 123456
```

## 範例輸出 #1

```
3
6
10
5
17
49
480224489
```
