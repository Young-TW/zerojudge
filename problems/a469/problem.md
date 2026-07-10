# a469. 10063 - Knuth's Permutation

## 內容

在Knuth的一本書"The Art of Computer Programming- Volume 1"有一些產生排列的技巧。其中有一個方法是這樣的：

對一個已經存在的排列：A1A2A3......An-1，如果要插入一個X，所有可能插入的方式為：

XA1A2A3......An-1，A1XA2A3......An-1，A1A2XA3......An-1，......，A1A2A3......XAn-1，A1A2A3,......An-1X

例如：從231這個排列要插入4在所有可能的地方，我們可以得到4231,2431,2341,2314

給你一個字元（英文字元）的集合，遵照以上的規則，你就可以產生所有的排列方式。給你的字元集合中所有的字元都不一樣，並且不會超過10個。產生的程序是遞迴的，你必須從第1個字元開始，並且按照順序的插入其他的字元。Sample Input和Sample Output會清楚的表達這一點。對Sample Input你的輸出應該完全和Sample Output一樣。

## 輸入說明

每筆測試資料一列，各有一字元的集合。

## 輸出說明

按照上面所提的方式，產生所有的排列方式。請注意輸入字元的順序對輸出是很重要的，也就是說 abc 和 bca 的輸出順序是不會一樣的。

測試資料間請空一列。

## 範例輸入 #1

```
abc
bca
dcba
```

## 範例輸出 #1

```
cba
bca
bac
cab
acb
abc

acb
cab
cba
abc
bac
bca

abcd
bacd
bcad
bcda
acbd
cabd
cbad
cbda
acdb
cadb
cdab
cdba
abdc
badc
bdac
bdca
adbc
dabc
dbac
dbca
adcb
dacb
dcab
dcba

```
