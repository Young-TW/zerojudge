# d873. 00465 - Overflow

## 內容

寫一個程式讀入兩個非負整數和一運算符號, 決定這兩個整數或是運算式產生的結果是否太大超出正常有號整數的範圍.(integer in Pascal, int in C)

## 輸入說明

每一列將包含一整數,一個運算子( + 或 *),和另一個整數.

## 輸出說明

對於每組輸入,先列出輸入,然後依照輸入可能會依順序印出 0-3行不同的訊息,這些訊息分別是: ``first number too big'', ``second number too big'', ``result too big''.

請參考Sample Output.

## 範例輸入 #1

```
300 + 3
9999999999999999999999 + 11
```

## 範例輸出 #1

```
300 + 3
9999999999999999999999 + 11
first number too big
result too big
```
