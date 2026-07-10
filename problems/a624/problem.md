# a624. 4. Password Analyzer

## 內容

你在一家成長中的電子商務網站工作，而它也成了竊賊覬覦的對象。竊賊以猜測密碼的方式來存取顧客的帳號，這常常是輕而易舉的 (如 "secret", "password", 和 "1234")。如果你的顧客使用較好的密碼，你的公司就可以省點力氣來處理盜刷的問題。

你被賦與的任務為設計一個密碼分析器以告知顧客他們所選的密碼的強度。一個「強」密碼以增加長度或混用字母、數字及符號來增加猜測的難度。在這項工作中，一個「強」 (strong) 密碼擁有以下所有特性： 

- 長度至少 8 個字元 (如："spookyfish")
- 同時有大寫及小寫字母 (如："sPookyFISH")
- 同時有字母及至少一個數字或符號 (如："sPookyFiSH3" 或 "$PookyFI3H")
 一個「好」 (good) 密碼擁有兩個上述的特性，一個「尚可」(acceptable) 密碼只擁有一個特性。不符合上述任何特性的則為「弱」(week) 密碼。請寫一個程式來分析所給的密碼的強度。

## 輸入說明

每筆測資一行，其中含有一個密碼，長度最大為 30 字元。密碼中沒有空白。

## 輸出說明

依據上述的特性，輸出所輸入密碼的強度。

## 範例輸入 #1

```
lizard
aardvark
Aardvark
Aardvark77
```

## 範例輸出 #1

```
This password is WEAK
This password is ACCEPTABLE
This password is GOOD
This password is STRONG
```
