# q908. 訊息排排隊-1

## 內容

Justin 是一位科技公司的上班族，在公司神秘的機房中存在三台電腦，分別扮演 producer、server 與 consumer 的角色。Producer 會生產訊息丟給 server 之中的 queue，並等待傳送給 consumer。已知 producer 每秒生產 p 個訊息給 server，consumer 每秒從 server 獲得 c 個訊息。若 server 從 producer 收到太多訊息來不及給 consumer，訊息就會累積在 server 之中。請問在 t 秒時，server 裡面的訊息會累積多少個？

## 輸入說明

輸入三個非負整數 p, c 與 t 以空白隔開。

0 ≤ p, c ≤ 109

1 ≤ t ≤ 109

## 輸出說明

輸出一個整數，代表 t 秒時，server 裡面訊息的累積個數。

## 範例輸入 #1

```
10 3 5
```

## 範例輸出 #1

```
35
```

## 範例輸入 #2

```
5 10 100
```

## 範例輸出 #2

```
0
```
