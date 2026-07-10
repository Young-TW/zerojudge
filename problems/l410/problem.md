# l410. 檔案總管-基本版

## 內容

小明電腦的檔案總管壞了，請你編程一段模擬檔案總管的程序，幫助小明解決問題。

## 輸入說明

輸入有若干行，以"stop"為結束，格式為 : "要執行的東西類型+名稱 動作 被執行的東西類型+名稱)


一開始甚麼都沒有的時侯，要執行的東西為"file manager"。


要執行的東西類型 : file/folder 名稱


動作 : add(新增) delete(刪除) cut(剪下) copy(複製) paste(貼上) (謹記paste的東西是上一次複製的東西 (剪下/複製的東西)


被執行的東西類型: file/folder 名稱


接下來為一個字串s，為上方出現過的folder名稱。

## 輸出說明

輸入只有一行，為s裡的所有file/folder，以升序排列(按名稱)。


格式 : "類型 名稱"


(例子 : a folder裡有b folder，但a不需輸入b folder裡的東西，只需輸出b folder和a folder裡的其他東西就行)

## 範例輸入 #1

```
file manager add folder abc
abc add file book
abc cut book
abc add folder others
others paste book
file manager paste book
file manager add folder me
fire manager copy me
abc paste me
book add dictionary
book copy dictionary
abc delete dictionary
abc add dictionary
stop
abc
```

## 範例輸出 #1

```
file dictionary
folder me
folder others
```
