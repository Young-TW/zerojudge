# e267. 11192 - Group Reverse

## 內容

Group reversing a string means reversing a string by groups.


以下為範例


"TOBENUMBERONEWEMEETAGAINANDAGAINUNDERBLUEICPCSKY"


此字串長度為48，假設我們把該字串分成8個長度為6的群組，對每個群組內的字串分別做反轉，會得到另一個新字串：


"UNEBOTNOREBMEEMEWENIAGATAGADNAEDNUNIIEULBRYKSCPC"


此行為就稱為Group reversing。


給定群組數目及字串，請你分組反轉字串。

## 輸入說明

每行包含一個整數G (G < 10)，表示群組數，當G為0代表輸入結束


接著是一個字符串，其長度為G的倍數。


字符串長度不大於100。


字符串僅包含英文字母。

## 輸出說明

對於每一行輸入，輸出此字符串的Group reversing。

## 範例輸入 #1

```
3 ABCEHSHSH
5 FAOETASINAHGRIONATWONOQAONARIO
0
```

## 範例輸出 #1

```
CBASHEHSH
ATEOAFGHANISTANOIRAQONOWOIRANO
```
