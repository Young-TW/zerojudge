# e548. 11995 - I Can Guess the Data Structure!

## 內容

有一個叫神奇袋子的數據結構，支持兩種操作：
1 x：將x放入神奇袋子
2：將其中一個元素拿出袋子
給定一系列具有回傳值的操作，你要猜測神奇袋子是什麼數據結構。
它可能是~~~
一個stack (Last-In, First-Out)
一個queue (First-In, First-Out)
一個priority-queue (Always take out larger elements first)
或者其他神奇的數據結構！！！

## 輸入說明

輸入有多組測資。
每組測資第一行為一個整數n (1 ≤ n ≤ 1000)。
接下來n行中，每一行可能是type-1命令，或者是type-2命令
type-2命令後會跟著一個數字x (0 < x ≤ 100)，x代表拿出來的數字。

## 輸出說明

對於每組測資輸出如下：
如果神奇袋子一定是stack
輸出"stack"
如果神奇袋子一定是queue
輸出"queue"
如果神奇袋子一定是priority queue
輸出"priority queue"
如果神奇袋子以上三種都不是
輸出"impossible"
如果神奇袋子不能確定是上述三種的那一種
輸出"not sure"

## 範例輸入 #1

```
6
1 1
1 2
1 3
2 1
2 2
2 3
6
1 1
1 2
1 3
2 3
2 2
2 1
2
1 1
2 2
4
1 2
1 1
2 1
2 2
7
1 2
1 5
1 1
1 3
2 5
1 4
2 4
```

## 範例輸出 #1

```
queue
not sure
impossible
stack
priority queue
```
