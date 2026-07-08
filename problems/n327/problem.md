# n327. The Tower of Names

## 內容

在英文裡，很多名字出現在一個清單時，常常會以英文字母排序 (Alphabetical Order)，方便人們查找。但是文文覺得這樣長短不一的名字混雜在一起，不太整齊，於是他就先用名字的長短排序，相同長度的名字才以字母排序，如此一來，當你把這名字的清單列出來是會是上窄下寬，看起來就像是一座塔。


給你若干個名字，請以文文的方式排序後輸出。

## 輸入說明

輸入的第一行含有一個整數 𝑛 (0 < 𝑛 <= 100)，接下來有 𝑛 行，每行含有一個由英文字母、句點 (.)、連字號 (-)、雙引號 (")、及空白所組成的英文姓名。

## 輸出說明

將輸入的姓名先以長度 (含中間的空白及其它符號) 排序，長度相同時，則以字母順序排序。

## 範例輸入 #1

```
5
Alexander Smith
Mia Johnson
Benjamin Lee
Isabella Chang
Oliver Taylor
```

## 範例輸出 #1

```
Mia Johnson
Benjamin Lee
Oliver Taylor
Isabella Chang
Alexander Smith
```

## 範例輸入 #2

```
4
Ethan Baker
April Adams
Jacob White
Emily Clark
```

## 範例輸出 #2

```
April Adams
Emily Clark
Ethan Baker
Jacob White
```
