# k413. Python 縮排檢查

## 內容

隨著二十世紀末「結構化程式設計」獲得多數電腦科學家的認同，用「縮排」來突顯程式中的區塊結構已變成普遍的「習慣」，它雖然大幅改善程式的可讀性，但是編譯器倒也不會去強制你使用縮排，直到 Python 的出現！


既然縮排如此重要，Python 便以它作為定義程式區塊的語法，一來強迫使用者建立縮排的良好習慣，二來就不需要像其他語言用 {}、[] 等括號或是 if ... end if、begin ... end 之類的關鍵字來標示區塊，讓程式更加簡潔！


以下是 Python 縮排的規則：


- 在同一區塊的程式碼必須上下對齊，也就是行首需有相同數量的空白，不可隨意縮排，否則會出現「unexpected indent」訊息。(參見範例 1)
- 會導入一個新的程式區塊的指令行都以「:」結尾，如 if、elif、else、while、for、def、try、except、with 等。其後的指令「必須」縮排 (indent, 增加行首空白數)，以定義一個新的區塊，否則會出現「expected an indented block」訊息。(參見範例 2)
- Python 以「取消縮排」 (unindent, 減少行首空白數) 來結束一個程式區塊，但是這行的縮排必須與它外層的某個區塊對齊，否則會出現「unindent does not match any outer indentation level」訊息。(參見範例 3)
- 程式的第一個區塊必須從第一個字元開始，沒有任何縮排，否則會出現第一條的訊息。

現在，請撰寫一個程式，來驗證輸入的 Python 程式碼是否具有正確的縮排。

## 輸入說明

輸入含有一個 Python 程式，行數不會超過 100 行。


為了簡化本題目，輸入的 Python 程式：


- 不會有「空行」或「註解」。
- 行末不會有白空白。也就是說，你可以用 s[-1] 來檢查行尾是否為「:」。
- 行首縮排只會有空白，不會有 Tab。你可以用 len(s) - len(s.lstrip()) 來計算行首有幾個空白。
- 不會使用顯式或隱式行接續 (explicit or implicit line continuation)。也就是不會把一行指令分成兩行或更多。
- 除了縮排，不會有其它語法錯誤。

## 輸出說明

如果輸入的 Python 程式縮排符合語法，請輸出「Indention OK」。


如果輸入的 Python 程式縮排有錯誤，請輸出錯誤所在的行數、該行程式碼內容，及題目指定的錯誤訊息。

## 範例輸入 #1

```
w = int(input())
  if w > 50:
    w -= 1
print(w)
```

## 範例輸出 #1

```
line 2
  if w > 50:
unexpected indent
```

## 範例輸入 #2

```
w = int(input())
if w > 50:
w -= 1
print(w)
```

## 範例輸出 #2

```
line 3
w -= 1
expected an indented block
```

## 範例輸入 #3

```
w = int(input())
if w > 50:
    w -= 1
  print(w)
```

## 範例輸出 #3

```
line 4
  print(w)
unindent does not match any outer indentation level
```

## 範例輸入 #4

```
w = int(input())
if w > 50:
    w -= 1
print(w)
```

## 範例輸出 #4

```
Indention OK
```
