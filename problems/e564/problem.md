# e564. 00540 - Team Queue

## 內容

Queues和Priority Queues是大部份的人都知道的資料結構。
然而，儘管Team Queue在日常生活中經常發生，但並不是眾所周知。
在Team Queue中，每個元素都屬於一個Team。如果某個元素進入Queue，它將首先從頭到尾搜索Queue，以檢查其teammates(同一Team的元素)是否已經在Queue中。
如果是，它將排在其Team的最後一個。如果不是，它將排在Queue最後面。
Dequeuing的方式與普通Queue中一樣：元素按照在Team Queue中出現的順序從頭到尾進行處理。
您的任務是寫一個程式模擬Team Queue。

## 輸入說明

輸入包含多組測資。
每組測資第一行為一個整數t (1 ≤ t ≤ 1000)，t代表有幾個Team。
如果t = 0代表輸入結束。
接下來t行
每行第一個整數n (1 ≤ n ≤ 1000)，代表該Team的成員數量。
之後跟著n個整數xi (0 ≤ xi ≤ 999999)。
接下來為若干個指令，以下為指令列表：
1. ENQUEUE x: 若x所屬的團隊成員已在Queue內，就排進Team內的最後一個。若沒有，則排進Queue的最後一個。
2. DEQUEUE: 將Queue最前面的元素移除，並輸出此元素。
3. STOP: 結束。
注意：實現的Team Queue需有效率，元素的Enqueing和Dequeuing都應僅花費恆定的時間。

## 輸出說明

對於每組測資，輸出"Scenario #k"，其中k是測資的編號。
接著對於每個"DEQUEUE"指令，將已出Queue的元素輸出。
在每組測資之後皆要輸出空白行。

## 範例輸入 #1

```
2
3 101 102 103
3 201 202 203
ENQUEUE 101
ENQUEUE 201
ENQUEUE 102
ENQUEUE 202
ENQUEUE 103
ENQUEUE 203
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
STOP
2
5 259001 259002 259003 259004 259005
6 260001 260002 260003 260004 260005 260006
ENQUEUE 259001
ENQUEUE 260001
ENQUEUE 259002
ENQUEUE 259003
ENQUEUE 259004
ENQUEUE 259005
DEQUEUE
DEQUEUE
ENQUEUE 260002
ENQUEUE 260003
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
STOP
0
```

## 範例輸出 #1

```
Scenario #1
101
102
103
201
202
203

Scenario #2
259001
259002
259003
259004
259005
260001
```
