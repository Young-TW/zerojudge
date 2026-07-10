# e544. 00612 - DNA Sorting

## 內容

在一個序列中，"unsortedness"是一種度量方式。
例如，在字母序列"DAABEC"中，因為在D的右側D比四個字母大，E的右側E比一個字母大，所以此度量為5。
該度量稱為序列的反轉數。
像是序列"AACEDGG"反轉數為1(幾乎已排序)。
而序列"ZWQM"反轉數為6(幾乎未排序)。
您負責對DNA字串序列進行分類。
但是，您不希望按字母順序對它們進行分類，而要按"sortedness"的順序對它們進行分類
並且從"sortedness"到"unsortedness"(反轉數小到反轉數大)。

## 輸入說明

輸入的第一行有一個整數T，T代表有幾組測資。
每組測資開頭有一個空白行。
接下來一行包含兩個整數n (0 < n ≤ 50)和m (0 < m ≤ 100)，n代表字串長度，m代表字串數量。
接下來是m行長度為n的字串。


測資中字串只包含大寫英文字母。

## 輸出說明

對於每組測資，輸出字串的列表，從"sortedness"到"unsortedness"。
如果兩個或兩個以上的字串反轉數相同，請以與輸入順序排序。
在連續的測資之間以空白行分隔。

## 範例輸入 #1

```
1

10 6
AACATGAAGG
TTTTGGCCAA
TTTGGCCAAA
GATCAGATTT
CCCGGGGGGA
ATCGATGCAT
```

## 範例輸出 #1

```
CCCGGGGGGA
AACATGAAGG
GATCAGATTT
ATCGATGCAT
TTTTGGCCAA
TTTGGCCAAA
```
