# r366. 10815 Andy’s First Dictionary

## 內容

Andy，8歲，有一個夢想——他想製作屬於自己的字典。這對他來說並不是件容易的事，因為他認識的單字數量嘛……還不太夠。不過，他有個聰明的主意：他從書架上挑出一本自己最喜歡的故事書，然後從中抄寫下所有不重複的單字。只要將這些單字按字母順序排列，他的字典就完成了！當然，這是一項非常耗時的工作，這時電腦程式就派上用場了。


你的任務是撰寫一個程式，列出輸入文本中所有不同的單字。在這個問題中，「單字」被定義為一連串連續的英文字母，無論是大寫或小寫。即使只有一個字母，也應視為一個單字。此外，你的程式必須對大小寫不敏感。舉例來說，像是 “Apple”、 “apple” 或 “APPLE” 都必須視為相同的單字。

## 輸入說明

輸入檔是一個文字檔，最多不超過 5000 行。每一行的字元數最多為 200 個。輸入以 EOF（檔案結尾）作為終止。

## 輸出說明

你的輸出應該列出輸入文字中出現的所有不同的單字，每個單字一行。所有單字都應該轉為小寫，並按字母順序排序。你可以確信，文本中不重複的單字總數不會超過 5000 個。

## 範例輸入 #1

```
Adventures in Disneyland
Two blondes were going to Disneyland when they came to a fork in the
road. The sign read: "Disneyland Left."
So they went home.
```

## 範例輸出 #1

```
a
adventures
blondes
came
disneyland
fork
going
home
in
left
read
road
sign
so
the
they
to
two
went
were
when
```
