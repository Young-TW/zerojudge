# e503. 00499 - What's The Frequency, Kenneth?

## 內容

#include <stdio.h>


main()
{
    int i;
     char *suffix[]= { "st", "nd", "rd" };
     char *item[]= { "Unix" , "cat", "sed", "awk", "grep", "ed", "vi"};
     printf("In the beginning, there was nothing.\n");
     for (i= 0; i < 7; i++)
         printf("And on the %d%s day, God created %s. And it was good.\n",
                    i + 1, (i < 3) ? suffix[i] : "th", item[i]);
}


神創造了好用的工具後，祂發現vi意圖使人墮落，因為vi功能強大，讓人不願意使用make, dbx, RCS等完善的工具
反而用了命令列來編譯、printf()來除錯。
所以上帝下了命令：
    因為工程師們褻瀆了我所創造的vi，所以我決定創造emacs，這是一個功能強大的文字編輯器
    工程師們只要用過一次vi，就必須受盡折磨，一路上將會如同地獄般哀鴻遍野
    工程師必須讀取很多列文字，並告訴我每一列中出現頻率最高的字母為何，及字母出現次數。
最後，我命令你們！！遵守我訂下的黃金法則：“不要讓你的朋友使用vi”

## 輸入說明

輸入包含很多列的文字

## 輸出說明

對於每列文字


請輸出出現頻率最高的字母，及字母出現次數


如果有多個字母頻率相同，請按照A-Z、a-z的順序輸出

## 範例輸入 #1

```
When riding your bicycle backwards down a one-way street, if the
wheel falls of a canoe, how many ball bearings does it take to fill
up a water buffalo?
Hello Howard.
```

## 範例輸出 #1

```
e 6
al 7
a 3
Hlo 2
```
