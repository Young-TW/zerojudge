# b050. 1. 集合運算

## 內容

數學集合各種運算以下列符號表示：

  x屬於(belong to)A記做 x  in  A

  A與B聯集(union)記做 A + B

  A與B交集(intersection)記做 A * B

  A與B差集(difference)記做 A – B

  A包含(contain)B記做 A >= B

  製作一個「集合」類別(set class)，使其能進行聯集、交集、差集、包含等運算。

## 輸入說明

每組測資的第一行 n 表示有 n 個集合，接著有 n 行分別為集合A、B、C…的內容。

  n=0 時表示輸入結束。

## 輸出說明

印出上述運算結果。

## 範例輸入 #1

```
2
abcdef
cfehi
2
34abcef
34
0
```

## 範例輸出 #1

```
Test Case 1:
A: {abcdef}
B: {cefhi}
A+B: {abcdefhi}
A*B: {cef}
A-B: {abd}
B-A: {hi}
A does not contain B
B does not contain A
Test Case 2:
A: {34abcef}
B: {34}
A+B: {34abcef}
A*B: {34}
A-B: {abcef}
B-A: {}
A contains B
B does not contain A
```
