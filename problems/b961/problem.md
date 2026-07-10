# b961. 3rd CPSC Problem 4－－Yojudge

## 內容

你使用過zerojudge，或又被稱作高中生程式解題系統的網站嗎？


　　如果你的答案是沒有，請至本次比賽網站，並到網站最上方，看看上面寫了些什麼。


　　號稱是程式設計專家的宥大師，認為zerojudge上的題目對他來說已經過於簡單，於是打算自製一個程式解題平臺──「Yojudge」。


　　在這個名叫「Yojudge」的網站上，將給各位帶來滿滿的程式解題題庫。在完成基本的架設工作，並出完題目後，接下來要做的就是寫一支Judge程式（能判斷使用者上傳的程式碼是否能通過的程式）了。


　　但事情沒有他想像之中那麼簡單，在他打算開工的時候，他發現網站上部分頁面的「Yojudge」竟然被討厭的自動校正軟體修改成了「You-judge」！為了避免進度的延宕，他只好請專業的你來協助他完成Judge程式。


　　對了，為預防這樣的烏龍再次發生，他向你交代了他的Judge程式應該要出現的所有判決解果及其意義。


- AC：表示使用者的輸入與正確解答完全相同（包含沒有多餘空白），且無逾時或超出記憶體使用限制等情況發生。
- WA：表示雖然沒有逾時或超出記憶體使用限制等情況發生，但使用者的輸入與正確解答並非完全相同。
- TLE：使用者的程式執行時間過久，超過了時間限制。
- MLE：使用者的程式執行時使用了過多的記憶體空間，超過了記憶體限制。
- OLE：使用者的程式輸出了超過正確解答的行數。

## 輸入說明

輸⼊包含多筆測資，每筆測資占多行，測資以EOF結尾。


　　每筆測資的第一行包含兩字串T1、M1，以空白隔開，分別為使用者程式的執行時間及使用的記憶體空間。


　　第二行以相同格式表示執行時間限制T2及記憶體空間限制M2。


　　接下來數行為使用者程式之輸出內容U，在其內容結束後，以一行「(This is the end of the user's output.)」（不含引號）結尾。請注意，本行並非使用者的輸出內容。


　　接下來數行為正確答案A，在其內容結束後，以一行「(This is the end of the correct answer.)」（不含引號）結尾。請注意，本行並非正確解答。


- 0ms ≤ T1、T2 ≤ 2min，格式為數字加上單位。當T1或T2小於或等於100毫秒時，單位以「ms」（毫秒，相當於10-3秒）表示，如：「100ms」；當T1或T2大於100毫秒且小於1分鐘時，單位以「s」（秒）表示，小數點後最多一位，如：「1.5s」、「3s」；當T1或T2大於1分鐘時，單位以「m」（分鐘，相當於60秒）及「s」表示（不一定會有「s」），如：「1min」、「1m30s」、「2min」。
- 0KB < M1、M2 < 1000MB，格式為數字加上單位。當M1或M2小於1000千位元組時，單位以「KB」（千位元組，相當於10-3MB）表示，如：「100KB」；當M1或M2大於或等於1000千位元組時，單位以「MB」（百萬位元組）表示，小數點後最多一位，如：「1MB」、「10.1MB」、「100MB」。
- U、A包含ASCII碼所有可顯示字元（ASCII碼32~126）及換行符號（ASCII碼10），且長度小於1000個字元。

## 輸出說明

對於每筆測資，請輸出一行，表示Judge程式的判決結果（各種判決結果所代表的意義請見題目敘述）。


　　若有多種判決結果同時發生，則仍輸出一種，輸出優先順序在前者。優先順序為：「TLE」、「MLE」、「OLE」、「WA」。

## 範例輸入 #1

```
0ms 292KB
1s 512MB
Number 1
(This is the end of the user's output.)
Number 1
(This is the end of the correct answer.)
1.2s 20KB
2s 1MB
 #2
(This is the end of the user's output.)
#2
(This is the end of the correct answer.)
1.5s 20MB
1s 1MB
number 3
(This is the end of the user's output.)
number  3
(This is the end of the correct answer.)
1s 200MB
1s 100MB
#4
(This is the end of the user's output.)
#04
(This is the end of the correct answer.)
1m30s 100.1MB
1m30s 100.1MB
#
5
(This is the end of the user's output.)
#5
(This is the end of the correct answer.)
```

## 範例輸出 #1

```
AC
WA
TLE
MLE
OLE
```
