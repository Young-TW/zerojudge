# d222. 11127 - Triple-Free Binary Strings

## 內容

Q11127: Triple-Free Binary Strings

二元字串是 0 和 1 組成的。給你一個二元字串 T，如果沒有二元字串 S，使得 SSS(三個 S 字串連起來)是 T 的子字串，那 T 就是 triple-free。
一個 pattern 包含 0, 1 還有星號(*)，星號可以被換成 1 或 0。例如，0**1 可以換成 0001, 0011, 0101, 0111，但是不能換成 1001 或 0000。


給你一個 pattern P，它可以換成多少種 triple-free 的字串？

## 輸入說明

每一行表示一組測資，包含 pattern 的長度 n(0 < n < 31)，還有 pattern P。最多有 35 組測資。
n=0 時表示輸入結束。

## 輸出說明

對每組測資，輸出 case number 和答案，如下所示。

## 範例輸入 #1

```
4 0**1
5 *****
10 **01**01**
0
```

## 範例輸出 #1

```
Case 1: 2
Case 2: 16
Case 3: 9
```
