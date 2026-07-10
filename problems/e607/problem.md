# e607. 00454 - Anagrams

## 內容

變位字謎是通過重新排列成一個單詞或短語的字母而形成另一個單詞或短語。
例如："carthorse"是“"rchestra"的變位字謎。
詞語內的空格在形成變位字謎時會被忽略。因此"orchestra"和"horse cart"也是變位字謎。
請你寫一個程式，該程式會讀取單詞或短語列表，並且輸出列表中出現的所有成對的變位字謎。

## 輸入說明

輸入第一行包含一個整數T，代表測資數量。
每組測資第一行為一空白行。
接下來每行為一個單詞或短語。
所有單詞或短語皆為小寫。
每組測資包含1到100行。

## 輸出說明

對於每組測資，輸出所有成對的變位字謎(列表中有可能沒有變位字謎)。
每行包含兩個用" = "分隔的變位字謎。
每組變位字謎應只輸出一次，並且輸出應按照字典順序排列。
如果第一個變位字謎(等號左邊)相同，則按照第二個變位字謎(等號右邊)的字典順序排列。
每組測資需用空白行分隔。

## 範例輸入 #1

```
1

carthorse
horse
horse cart
i do not know u
ok i now donut
orchestra
```

## 範例輸出 #1

```
carthorse = horse cart
carthorse = orchestra
horse cart = orchestra
i do not know u = ok i now donut
```
