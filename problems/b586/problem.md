# b586. 文章壓縮

## 內容

有一種壓縮文件內沒有數字0,1,2,...,9的方法，你需要建立一個 Linked List 來紀錄出現過的文字(word)，文章內除了大小寫英文字母外都視為非文字(not a word)或是分隔文字(word)的判斷。


每讀到一個還沒出現過的文字(word)就放進 Linked List 的頭，如果讀入的文字已經出現在 Linked List 之中，就把這個文字出現在 Linked List 的位置索引值輸出，索引值從 1 開始，並把文字Linked List內該文字移動到最前方後繼續。操作細節請參考範例及提示。


寫一個程式依照上述方式壓縮文件，你可以假設每一個文字(word)不會超過50個字母，而且文章中不會有數字出現

大小寫不同的文字視為不同，例如"abc" 和 "Abc" 是不同的文字, 非大小寫字母都視為分隔符號
"x-ray"      包含 2 個文字: x, ray
"Mary's"    包含 2 個文字: Mary, s
"It's a winner"     包含 4 個文字: It, s, a, winner

## 輸入說明

輸入文章內的文字數目沒有上限，文章內除了最後一行的 0 之外不會出現任何數字，遇到 0 就結束，不必輸出最後的 0

## 輸出說明

依照上述規則輸出經過壓縮後的文章資料

## 範例輸入 #1

```
Dear Sally,
   Please, please do it--it would please
Mary very, very much. And Mary would
do everything in Mary's power to make
it pay off for you.

    -- Thank you very much --
0
```

## 範例輸出 #1

```
Dear Sally,
   Please, please do it--1 would 4
Mary very, 1 much. And 4 6
8 everything in 5's power to make
14 pay off for you.

    -- Thank 2 18 18 --
```
