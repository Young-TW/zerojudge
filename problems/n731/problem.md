# n731. 10188 - Automated Judge Script

## 內容

來自程式設計競賽的評審以非常刻薄和懶惰著稱。我們這些評審希望工作量少，錯誤答案更多！所以，我們需要你的幫助，編寫一個自動評審腳本來評估來自世界各地團隊的解題結果。你需要寫一個程序，接收標準答案和團隊輸出，並給出以下其中一個訊息作為答案：


「Accepted」：由於我們非常刻薄，只要團隊的輸出與標準答案完全匹配，才會給出「Accepted」的答案。也就是說，所有字符必須匹配，且順序也必須一致。


「Presentation Error」：如果所有數字字符匹配（且順序一致），但至少有一個非數字字符錯誤（或順序錯誤），則給出「Presentation Error」。例如，‘15 0’和‘150’會收到‘Presentation Error’，而‘15 0’和‘1 0’不會（它會收到‘Wrong Answer’，見下文）。


「Wrong Answer」：如果團隊的輸出不符合上述任何一個標準，那麼只能給出‘Wrong Answer’的答案！

## 輸入說明

輸入將包含任意數量的輸入組。每組輸入以一個小於 100 的正整數 n 開始，單獨一行，描述標準解答的行數。接下來的 n 行包含標準解答。然後是一個小於 100 的正整數 m，單獨一行，描述隊伍輸出的行數。接下來的 m 行包含隊伍輸出。當 n 的值為 0 時，輸入結束，不應再進行處理。 每行不會超過 120 個字符。

## 輸出說明

對於每組輸入，你應輸出以下其中一行：


Run #x: Accepted
Run #x: Presentation Error
Run #x: Wrong Answer


其中，x 表示輸入組的編號（從 1 開始）。

## 範例輸入 #1

```
2
The answer is: 10
The answer is: 5
2
The answer is: 10
The answer is: 5
2
The answer is: 10
The answer is: 5
2
The answer is: 10
The answer is: 15
2
The answer is: 10
The answer is: 5
2
The answer is: 10
The answer is: 5
3
Input Set #1: YES
Input Set #2: NO
Input Set #3: NO
3
Input Set #0: YES
Input Set #1: NO
Input Set #2: NO
1
1 0 1 0
1
1010
1
The judges are mean!
1
The judges are good!
0
```

## 範例輸出 #1

```
Run #1: Accepted
Run #2: Wrong Answer
Run #3: Presentation Error
Run #4: Wrong Answer
Run #5: Presentation Error
Run #6: Presentation Error
```
