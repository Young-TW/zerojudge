# e543. 00401 - Palindromes

## 內容

迴文字串是一串數字或字母，從左到右讀取和從右到左讀取相同。
例如，"ABCDEDCBA"是迴文字串。
鏡像字串是一種字串，當該字串的每個元素更改為鏡像(如果它具有鏡像)並且從右到左讀取該字串時，其結果與從左到右讀取原始字串相同。
例如，"3AIAE"是鏡像字符串，因為"A"的鏡像和"I"的鏡像是他們自己，而"3"和"E"為彼此的鏡像。
鏡像迴文是指符合迴文字串標準和鏡像字串標準的字串。
例如，"ATOYOTA"是一個鏡像迴文，"A"、"T"、"O"、"Y"為彼此的鏡像。
該字串從左到右讀取和從右到左讀取相同。
並且每個字元都鏡像替換後從右到左讀取結果，與從左到右讀取原始字串相同。


以下為有效字元鏡像對應表：



![image](ShowImage?id=2399)


請注意，"0"(零)和"O"(字母)被視為相同字符，因此只有字母"O"是有效字符。

## 輸入說明

輸入每行有一個字串s (1 <= s長度 <= 20)。
任何字串中都不會包含無效字符。

## 輸出說明

對於每個輸入字串，按照以下輸出
此字串屬於鏡像迴文
輸出"s -- is a mirrored palindrome."
此字串屬於鏡像字串
輸出"s -- is a mirrored string."
此字串屬於迴文字串
輸出"s -- is a regular palindrome."
此字串甚麼都不是
輸出"s -- is not a palindrome."
其中s代表原始字串


此外，在每行輸出之後，需要再輸出換行。

## 範例輸入 #1

```
NOTAPALINDROME
ISAPALINILAPASI
2A3MEAS
ATOYOTA
```

## 範例輸出 #1

```
NOTAPALINDROME -- is not a palindrome.

ISAPALINILAPASI -- is a regular palindrome.

2A3MEAS -- is a mirrored string.

ATOYOTA -- is a mirrored palindrome.
```
