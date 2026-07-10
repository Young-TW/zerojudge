# m273. 10361 - Automatic Poetry

## 內容

"天哪！！" Lara Croft 驚呼道："又是這些愚蠢的謎語之一！"
在《古墓奇兵 14》中，蘿拉一如既往地在古埃及金字塔、史前洞穴和中世紀走廊中殺出一條血路。 現在她正站在一個重要的日耳曼式門口前，必須解決一個語言謎題才能通過。 像往常一樣，這個謎語在智力上並不是很有挑戰性。
這次，謎語涉及包含"Schuttelreim"的詩歌。 以下短詩是 Schuttelreim 的一個例子：


    Ein Kind halt seinen Schnabel nur,
    wenn es hangt an der Nabelschnur.


Note：德國用戶請見諒。 我必須修改一些內容，因為它們沒有以純文字格式正確顯示。


Schuttelreim 似乎是典型的德國發明。 這種奇怪類型的詩歌的有趣之處在於，如果有人給你第一行和第二行的開頭，你就可以自己完成這首詩。 好吧，即使電腦也可以做到這一點，而你的任務就是寫一個程式來自動完成它們。 這將幫助勞拉專注於《古墓奇兵》的「action」部分，而不是「intellectual」部分。

## 輸入說明

第一行為一個數字 n 。 在此行之後為 n 對 Schuttelreims 詩歌。


每對的第一行的形式為


S1 < S2 > S3 < S4 > S5


其中 Si 可能為空、小寫字串或空格。


每對的第二行是一串小寫字元或空格，以三個點「...」結尾。


每行的長度最多為 100 個字元

## 輸出說明

對於每對 Schuttelreim 詩歌 L1 和 L2，請輸出 C1 和 C2：


C1 與 L1 相同，只是去掉了「<」和「>」。


C2 與 L2 相同，除了應該出現字串 S4 S3 S2 S5 而不是三個點。

## 範例輸入 #1

```
3
ein kind haelt seinen <schn>abel <n>ur
wenn es haengt an der ...
weil wir zu spaet zur <>oma <k>amen
verpassten wir das ...
<d>u <b>ist
...
```

## 範例輸出 #1

```
ein kind haelt seinen schnabel nur
wenn es haengt an der nabel schnur
weil wir zu spaet zur oma kamen
verpassten wir das koma amen
du bist
bu dist
```
