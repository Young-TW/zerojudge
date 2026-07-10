# l418. 檔案總管-進階版

## 內容

續上題，l410. 檔案總管-基本版，這次小明想做得迫真一點，因此他決定模擬出檔案裡的內容。


另外，他也希望能模擬出windows系統的win+v剪貼簿功能。


現假設所有檔案均為文字檔，請你編寫一段程序協助小明解決問題。

## 輸入說明

輸入有若干行，以"stop"為結束，格式為 : "要執行的東西類型+名稱 動作 被執行的東西類型+名稱)


一開始甚麼都沒有的時侯，要執行的東西為"file manager"。


要執行的東西類型 : file/folder 名稱


動作 : add(新增) delete(刪除) cut(剪下) copy(複製) paste(貼上) (謹記paste的東西是上一次複製的東西 (剪下/複製的東西)


如果為第一次新增該file，則格式為 " folder名稱 add file名稱 內容"


貼上的格式為 " folder名稱 paste 最後?個複製(數字)"


被執行的東西類型: file/folder 名稱


接下來為一個字串s，為上方出現過的folder名稱。


最後一行為一個字串l，代表一個檔案名稱。


保證"最後?個複製"和內容的長度均<=10。

## 輸出說明

輸入只有一行，為s裡的所有file/folder，以升序排列(按名稱)。


格式 : "類型 名稱"


(例子 : a folder裡有b folder，但a不需輸入b folder裡的東西，只需輸出b folder和a folder裡的其他東西就行)


最後一行輸出l的內容。

## 範例輸入 #1

```
file manager add folder time
time add file time2 hi
time copy time2
file manager copy time
file manager add folder book
book paste 1
book add folder comic
comic paste 2
comic add file novel good
stop
book
time2
```

## 範例輸出 #1

```
folder comic
folder time
file time2
hi
```
