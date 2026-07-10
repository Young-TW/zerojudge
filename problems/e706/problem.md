# e706. 12820 - Cool Word

## 內容

"word"的定義是一串小寫字母組成的單詞。
"cool word"的定義是此單詞至少包含2個不同的字母，每個不同字母的出現次數皆不相同。


正式的定義如下：
令 w 為一個"word"，S 為 w 中的字母集合，令 f(c) 表示w中c出現的次數(c 皆在 S 集合範圍內)。
當所有 f(c) 皆不相同時，w為一個"cool word"。


例如："ada"為一個"cool word"，因為 f(a) = 2，f(d) = 1，並且字母不相同。
"banana"也為一個"cool word"，因為f(a) = 3，f(n) = 2，f(b) = 1。
"bbacccd"不是一個"cool word"，因為f(a) = f(d) = 1。
其他一些"cool word"包括：mammal, needed, papaya, referee, senselessness。


請你讀取單詞列表並且計算"cool word"的數量。

## 輸入說明

輸入包含多組測資。
每組測資第一行為一個整數n (1 ≤ n ≤ 10000)，代表單詞列表長度。
接下來n行，每行包含一個單詞，該單詞包含至少1個且最多30個字母。

## 輸出說明

對於每組測資，輸出測資case編號以及"cool word"的數量。

## 範例輸入 #1

```
2
ada
bbacccd
2
illness
a
```

## 範例輸出 #1

```
Case 1: 1
Case 2: 0
```
