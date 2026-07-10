# i524. 11988: Broken Keyboard (a.k.a. Beiju Text)

## 內容

你用了一個有點壞掉的鍵盤打字，該鍵盤會自動按下” Home”鍵與"End"鍵，直到打完整個內容以前，你都沒有發現到這個問題。本題給定鍵盤輸出的字串 (包含Home與End)，請你輸出該字串在螢幕顯示的內容。

## 輸入說明

輸 入有多組測試資料，每組一列，其長度介於1 ~ 100,000之間，包含大小寫的字母，底線及兩個符號 '[' 與 ']'。 '['表示Home鍵(被鍵盤自動按下)，']'表示End鍵(被鍵盤自動按下)。


輸入資料以EOF表示結束。

## 輸出說明

對每組冊資，請輸出該輸入字串在螢幕上顯示的內容。

## 範例輸入 #1

```
This_is_a_[Beiju]_text
[[]][][]Happy_Birthday_to_Tsinghua_University
```

## 範例輸出 #1

```
BeijuThis_is_a__text
Happy_Birthday_to_Tsinghua_University
```
