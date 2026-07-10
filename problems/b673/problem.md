# b673. How Big Is It

## 內容

Ian is going to California, and he has to pack his things, including his collection of circles. Given a set of circles, your task is to write a program to find the smallest rectangular box in which they fit. All circles must touch the bottom of the box. The figure below shows an acceptable packing for a set of circles (although this may not be the optimal packing for these particular circles). Note that in an ideal packing, each circle should touch at least one other circle (but you probably figured that out).


Ian要去加州，他必須打包他的東西:一堆圓型。 給定一組圓的半徑，你的任務是寫一個程式，找到它們適合的最小長方形框。 所有圓形都必須觸及長方形底部。 下圖顯示了一組圓的可接受包裝（儘管這可能不是這些特定圓的最佳包裝）。 注意，一個理想的包裝，每個圓應該至少接觸另一個圓。

![image](ShowImage?id=887)

## 輸入說明

The input data contains several test cases. Each test case consists of only one line. Each line contains several numbers, separated by spaces. The first number is a positive integer m, m <= 8, which indicates the number of circles in the test case. The next m numbers are the radius of the circles which have to be packed in a single box. These numbers may not be integers. A line with 0 signifies the end of input.


輸入數據包含數個測試資料。 每筆測試資料只包含一行。 每行包含幾個數字，用空格分隔。 第一個數字是一個正整數m，m <= 8，表示測試用例中的圓圈數。 接下來的m個數字是必須在單個框中打包的圓的半徑。 這些數字可能不是整數。 0開頭的那行表示輸入結束。

## 輸出說明

For each test case, your program has to output the size of the smallest rectangle which can pack the circles. Each output has to be on a separate line by itself, with three places after the decimal point. Do not output leading zeroes unless the number is less than 1, e.g. 0.543.


對於每筆測試資料，您的程序必須輸出可以打包圓的最小矩形的大小。 每個輸出必須在一行內，輸出小數點後三個位置。 除非數字小於1，否則不輸出前導零，例如。 0.543。

## 範例輸入 #1

```
3 2.0 1.0 2.0
4 2.0 2.0 2.0 2.0
3 2.0 1.0 4.0
0
```

## 範例輸出 #1

```
9.657
16.000
12.657
```
