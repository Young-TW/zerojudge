# f435. 10267-Graphical Editor

## 內容

簡單的圖形編輯器處理一個矩形表M×N（1≤M，N≤250）。表格的每個像素都有其顏色。圖片由該正方形像素形成。
問題是編寫一個程序，該程序模擬圖形編輯器的交互工作。


The simple graphical editor deals with a rectangular table M × N (1 ≤ M, N ≤ 250). Each pixel of the table has its colour. The picture is formed from this square pixels.
The problem is to write a program, which simulates an interactive work of the graphical editor.

## 輸入說明

輸入由編輯器命令組成，每行一個。每個命令由一個拉丁大寫字母表示放置在該行的開頭
如果命令使用參數，則所有參數將在同一行中用空格隔開
顏色：用大寫英文字母表示
文件名中沒有空格
請支援以下操作：
I M N：創造M×N的表格且每個像素的顏色為O
C:使目前的表格顏色全為O
L X Y C:使(X,Y)的像素顏色為C
V X Y1 Y2 C：使(X,Y1)...(X,Y2)的顏色為C
H X1 X2 Y C：使(X1,Y)...(X2,Y)的顏色為C
K X1 Y1 X2 Y2 C：使由(X1,Y1)為左上角,(X2,Y2)為右下角組成的矩形中所有的像素顏色為C
F X Y C：使(X,Y)附近與它同顏色的像素顏色為C(就是小畫家中滴管)
S Name：輸出Name之後輸出目前的表格
X：停止操作


Input consists of the editor commands, one per line. Each command is represented by one Latin capital
placed in the very beginning of the line. If the command supposes parameters, all the parameters will
be given in the same line separated by space. As the parameters there may be: the coordinates of the
pixel - two integers, the first one is the column number and belongs to 1...M, the second one is the
row number and belongs to 1...N, the origin is in the upper left corner of the table; the colour - the
Latin capital; file name - in MSDOS 8.3 format.
The editor deals with the following commands:
I M N：Creates a new table M ×N. All the pixels are colored in white (O).
C：Clears the table. The size remains the same. All the pixels became white (O).
L X Y,C：Colors the pixel with coordinates (X, Y ) in colour C.
V X Y1 Y2 C：Draws the vertical segment in the column X between the rows Y1 and Y2 inclusive in colour C.
H X1 X2 Y C：Draws the horizontal segment in the row Y between the columns X1 and X2 inclusive in colour C.
K X1 Y1 X2 Y2 C：Draws the filled rectangle in colour C. (X1, Y1) is the upper left corner, (X2, Y2) is the lower right corner of the rectangle.
F X Y C：Fills the region with the colour C. The region R to be filled is defined as follows. The pixel (X, Y ) belongs to this region. The other pixel belongs to the region R if and only if it has the same colour as pixel (X, Y ) and a common side with any pixel which belongs to this region.
S Name：Writes the picture in the file N ame.
X：Terminates the session.

## 輸出說明

每次遇到"S NAME"命令時，都應輸出文件名"NAME"和當前的表格。每行均由像素的顏色系列表示，請參見輸出示例。
如果命令中的字符不同於I，C，L，V，H，K，F，S，X，編輯器應忽略整行


Every time the command ‘S NAME’ meets, you should output the file name NAME and the current
table, row by row. Each row is represented by a pixels’ colours series, see the output sample.
Errors: If as a command there will be a character different from I, C, L, V, H, K, F, S, X, the
editor should ignore the whole line and pass to the next command.
In case of other errors the program behaviour is unpredictable.

## 範例輸入 #1

```
I 5 6
L 2 3 A
S one.bmp
G 2 3 J
F 3 3 J
V 2 3 4 W
H 3 4 2 Z
S two.bmp
X
```

## 範例輸出 #1

```
one.bmp
OOOOO
OOOOO
OAOOO
OOOOO
OOOOO
OOOOO
two.bmp
JJJJJ
JJZZJ
JWJJJ
JWJJJ
JJJJJ
JJJJJ
```
