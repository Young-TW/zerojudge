# b110. 3. 黑白影像的四分樹表示法

## 內容

![image](images/problems/b110.gif)

![image](images/problems/b110_1.gif)

## 輸入說明

![image](images/problems/b110_2.gif)

## 輸出說明

對每一個輸入的黑白影像，將其四分樹表示法以 b, w, g 三個符號，依深先表 示法順序列出(每個輸出符號之間有一個空白隔開)。

## 範例輸入 #1

```
4
0000
0100
0011
0011
4
1000
0110
0110
0000
8
 
00001111
00001111
00101111
00101111
00000000
00000000
00000011
00001111
```

## 範例輸出 #1

```
g w g w w w b w b
g g w w b w g w b w b g b w w w g w b w w
g b g w w w g w b b w w g w w g w w b b b
```
