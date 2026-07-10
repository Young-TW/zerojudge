# a131. 00739 - Soundex Indexing

## 內容

Soundex 指數系統的開發是為了將發音或拼字相似的名字的編碼以方便取用。它被美國戶口普查局所採用，許多州也用它來為駕照編碼。你的任務是讀取一連串的名字，一個一行，計算 Soundex 碼，並把名字和編碼寫到輸出，(每個名字一行)。

每個名字包含 1 到 20 個大寫字母 (ASCII 碼 65 到 90)，長度不到 20 個字元的名字後面不會補空白。因此名字只會有大寫字母。

如何產生 Soundex 碼：Soundex 碼含有一個字母及其後的三位數字。其編碼規則如下： 

1. 名字的第一個字母成為編碼中第一且唯一的字母。2. A, E, I, O, U, Y, W 及 H 等字母不列入編碼，但可以拆散兩個連續編碼 (參見下一條)。3. 其餘的字母都必需編碼，除非它緊跟在一個編碼相同的字母之後。4. Soundex 編碼表為： 

CodeKey Letters and Equivalents1B, P, F, V2C, S, K, G, J, Q, X, Z3D, T4L5M, N6R 

5. 所有名字的編碼都是一位字母加三位數字，不足的位數補 0。6. 第三位數字之後的編碼捨去。

## 輸入說明

輸入檔包含名字的表列，每行一個。每個名字不會超過 20 個字元，只用到太寫字母。你的程式要持繼讀取名字直到偵測到檔尾。

## 輸出說明

輸出檔要包含名字及 Soundex 編碼兩欄。輸入檔的第一行中要分別在第 10 及第 35 字元輸出 "NAME" 及 "SOUNDEX CODE"。在標題之後，名字和編碼要出現在第 10 和第 35 字元，每組一行。在最後一個名字的下一行的第 20 個字元要出現 "END OF OUTPUT" 。

## 範例輸入 #1

```
LEE
KUHNE
EBELL
EBELSON
SCHAEFER
SCHAAK
```

## 範例輸出 #1

```
NAME                     SOUNDEX CODE
         LEE                      L000
         KUHNE                    K500
         EBELL                    E140
         EBELSON                  E142
         SCHAEFER                 S160
         SCHAAK                   S200
                   END OF OUTPUT
         |         |              |
         |         |              |__ Column 35
         |         |__ Column 20
         |__ Column 10
```
