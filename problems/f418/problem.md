# f418. Word Search Puzzle

## 內容

Word Search Puzzle 是一種常見的英文字謎，通常由一個矩形的方格所構成，每一個方格中有一個字母。玩家可以由左至右、由上至下，或是由左上至右下找到連續的字母拼成指定的單字。


文文已經找到了一個單字，給你起始及結束的位罝，麻煩你把這個單字拼出來。


 



![image](ShowImage?id=1627)

## 輸入說明

輸入的第一行含有六個整數 h (1 ≤ h ≤ 20), w (1 ≤ w ≤ 50), 代表字謎的高度與寬度，r1, c1 及 r2, c2 分別為起始及結束位置，r1, r2 是由上而下第幾列，c1, c2 是由左而右第幾個字元。(1 ≤ r1 ≤ r2 ≤ h, 1 ≤ c1 ≤ c2 ≤ w)


接下來的 h 行，每行有 w 個大寫字母，代表這個字謎的內容。

## 輸出說明

輸出由起始位置到結束位置的連續字元所拼成的單字。

## 範例輸入 #1

```
10 14 4 3 10 9
VBREEFISHRACHP
ANACROCODILEEB
AOSTRICHTEGRDA
IADDHCHEETAHGD
BHRODRAVENENEG
EYWDLSAMOLELHE
ARTPVPRCBOLROR
RHTOAAHCROWAGH
CCANNORIAZEBRA
HANYTAEKNINAWA
```

## 範例輸出 #1

```
DOLPHIN
```

## 範例輸入 #2

```
3 4 1 1 3 1
ROAR
OINK
WOOF
```

## 範例輸出 #2

```
ROW
```
