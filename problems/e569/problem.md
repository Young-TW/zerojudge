# e569. 00245 - Uncompress

## 內容

如果想要壓縮不包含數字字元的文件，可以用一個簡單的方法。
此壓縮方法需要列出未壓縮文件中的單詞list。
在未壓縮文件中遇到非字母字符時，會將其直接複製到壓縮文件中。
在未壓縮文件中遇到單詞時，如果該單詞為首次出現，將其直接複製到壓縮文件中，此情況下，單詞會放在list的最前面。
如果不是第一次出現，則不會將該單詞複製到壓縮文件中。而是將其在list中的位置複製到壓縮文件中，並將單詞移到list的開頭。
list位置的編號從1開始。
請你寫一個程式，將壓縮文件作為輸入，並且輸出原始文件。

## 輸入說明

輸入為多行，在壓縮文件中，沒有單詞超過50個字元，並且原始文件不包含數字字元。
單詞區分大小寫，單詞"abc"和單詞"Abc"不同。
另外，"x-ray"包含兩個單詞"x"、"ray"。
"Mary's"包含兩個單詞"Mary"、"s"。
"It's a winner"包含四個單詞"It"、"s"、"a"、"winner"。
文件中不同單詞的數量沒有上限。
如果該行只有一個"0"代表輸入結束(不用處理此行)

## 輸出說明

請輸出原始文件。

## 範例輸入 #1

```
Dear Sally,

    Please, please do it--1 would 4
Mary very, 1 much. And 4 6
8 everything in 5's power to make
14 pay off for you.

    -- Thank 2 18 18--
0
```

## 範例輸出 #1

```
Dear Sally,

    Please, please do it--it would please
Mary very, very much. And Mary would
do everything in Mary's power to make
it pay off for you.

    -- Thank you very much--
```
