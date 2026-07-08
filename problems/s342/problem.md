# s342. vector練習題: 三角形判斷以及歸類

## 內容

下面有N組木棒組，每組由三個木棒組成，有些木棒可以組成三角形
請找出可以組成三角形的木棒列印出來，並且歸類

- not triangle (非三角形)
- acute angle (銳角)
- obtuse angle (鈍角)
- right angle (直角)

## 輸入說明

每行先一字元後再三個數字代表三角形三邊(用空白隔開)

-1結束

## 輸出說明

Not Triangle:(空格)str,str,str...
Acute Angle:(空格)str,str,str...
Obtuse Angle:(空格)str,str,str...
Right Angle:(空格)str,str,str...

若該分類群沒有任何木棒組，就列印"(空格)None"
*請按照英文字母由小到大順序排列。

## 範例輸入 #1

```
A 3 4 5
B 6 8 10
C 4 5 6
D 3 3 3
E 5 9 20
F 6 6 11
-1
```

## 範例輸出 #1

```
Not Triangle: E
Acute Angle: C,D
Obtuse Angle: F
Right Angle: A,B
```

## 範例輸入 #2

```
A 3 4 5
B 6 8 10
C 4 5 6
D 3 3 3
E 5 9 20
F 6 6 6
G 7 19 111
H 20 333 23
-1
```

## 範例輸出 #2

```
Not Triangle: E,G,H
Acute Angle: C,D,F
Obtuse Angle: None
Right Angle: A,B
```

## 範例輸入 #3

```
A 3 4 5
B 6 8 10
C 4 5 6
K 10 10 6
M 2 2 2
P 2 3 4
L 1 2 4
E 5 9 20
F 6 6 6
G 7 19 111
H 20 333 23
-1
```

## 範例輸出 #3

```
Not Triangle: E,G,H,L
Acute Angle: C,F,K,M
Obtuse Angle: P
Right Angle: A,B
```
