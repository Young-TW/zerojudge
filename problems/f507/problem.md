# f507. 1207 - AGTC

## 內容

給你兩個字串S、T問把S變T最少要操作幾次，能做的操作如下：
1、刪除一個字元
2、增加一個字元
3、把一個字元換成另一個字元


Let x and y be two strings over some finite alphabet A. We would like to transform x into y allowing only operations given below:
Deletion: a letter in x is missing in y at a corresponding position.
Insertion: a letter in y is missing in x at a corresponding position.
Change: letters at corresponding positions are distinct
Certainly, we would like to minimize the number of all possible operations.
Illustration
A G T A A G T * A G G C
|  |  |            |       |      |  |
A G T * C * T G A C G C
Deletion: ∗ in the bottom line
Insertion: ∗ in the top line
Change: when the letters at the top and bottom are distinct
This tells us that to transform x = AGTCTGACGC into y = AGTAAGTAGGC we could be required to perform 5 operations (2 changes, 2 deletions and 1 insertion).
If we want to minimize the number operations, we should do it like
A G T A A G T A G G C
|  |  |         |       |      |  |
A G T C T G * A C G C
and 4 moves would be required (3 changes and 1 deletion).
In this problem we would always consider strings x and y to be fixed, such that the number ofletters in x is m and the number of letters in y is n where n ≥ m.
Assign 1 as the cost of an operation performed. Otherwise, assign 0 if there is no operation performed.
Write a program that would minimize the number of possible operations to transform any string x into a string y.

## 輸入說明

每筆測資有兩行
第一行是S的長度和字串S(|S|<1039)
第二行是T的長度和字串T(|T|<1039)


Input contains several datasets. Each dataset consists of the strings x and y prefixed by their respective lengths, one in each line.

## 輸出說明

輸出最少要操作幾次


For each dataset, an integer representing the minimum number of possible operations to transform any string x into a string y.

## 範例輸入 #1

```
10 AGTCTGACGC
11 AGTAAGTAGGC
```

## 範例輸出 #1

```
4
```
