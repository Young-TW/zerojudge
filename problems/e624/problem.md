# e624. 10340 - All in All

## 內容

你設計了一種新的加密技術，該技術通過在訊息字串之間插入隨機生成的字串來對消息進行編碼。
由於未解決專利問題，我們將不詳細討論如何生成字串。但是，要驗證您的方法，有必要寫一個程式來檢查訊息是否真正編碼在最終字串中。
給定兩個字串s和t，您必須確定s是否為t的原始訊息字串，即是否可以從t中刪除字元以使其剩餘字元串聯爲s。

## 輸入說明

輸入包含多行。
每行兩個字串s和t，s和t只會有英文字母。

## 輸出說明

對於每行輸入
如果s是t的原始訊息字串
輸出"Yes"
否則
輸出"No"

## 範例輸入 #1

```
sequence subsequence
person compression
VERDI vivaVittorioEmanueleReDiItalia
caseDoesMatter CaseDoesMatter
```

## 範例輸出 #1

```
Yes
No
Yes
No
```
