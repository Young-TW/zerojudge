# k627. L shaped plots (L形圖)

## 內容

Given a grid of R rows and C columns each cell in the grid is either 0 or 1.


A segment is a nonempty sequence of consecutive cells such that all cells are in the same row or the same column. We define the length of a segment as the number of cells in the sequence.


A segment is called "good" if all the cells in the segment contain only 1s.


An "L-shape" is defined as an unordered pair of segments, which has all the following properties:


- Each of the segments must be a "good" segment.
- The two segments must be perpendicular to each other.
- The segments must share one cell that is an endpoint of both segments.
- Segments must have a length of at least 2.
- The length of the longer segment is twice the length of the shorter segment.

We need to count the number of L-shapes in the grid.


Below you can find two examples of correct L-shapes,



![image](ShowImage?id=3272)


and three examples of invalid L-shapes.



![image](ShowImage?id=3273)


Note that in the shape on the left, two segments do not share a common endpoint. The next two shapes do not meet the last requirement, as in the middle shape both segments have the same length, and in the last shape the longer segment is longer than twice the length of the shorter one.


給定一個由 R 行和 C 列組成的網格，網格中的每個單元格要麼為 0，要麼為 1。


段是連續單元格的非空序列，所有單元格都在同一行或同一列中。我們將段的長度定義為序列中的單元格數。


如果段中的所有單元格僅包含 1，則該段稱為“好”。


“L 形”被定義為一對無序線段，它具有以下所有屬性：


每個段都必須是“好”段。
兩個線段必須相互垂直。
這些線段必須共享一個單元格，該單元格是兩個線段的端點。
段的長度必須至少為 2。
較長段的長度是較短段長度的兩倍。


我們需要計算網格中 L 形的數量。


您可以在下面找到兩個正確的 L 形示例，



![image](ShowImage?id=3274)


以及三個無效 L 形示例。



![image](ShowImage?id=3275)


請注意，在左側的形狀中，兩個線段不共享公共端點。接下來的兩個形狀不滿足最後一個要求，因為在中間形狀中，兩個段的長度相同，而在最後一個形狀中，較長段的長度是較短段長度的兩倍。

## 輸入說明

The first line of the input contains the number of test cases, T. T test cases follow.


The first line of each test case contains two integers R and C.


Then, R lines follow, each line with C integers representing the cells of the grid.


 


輸入的第一行包含測試用例的數量，T。緊隨其後的是 T 個測試用例。


每個測試用例的第一行包含兩個整數 R 和 C。


然後是 R 行，每行有 C 個整數，代表網格的單元格。

## 輸出說明

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the number of L-shapes.


對於每個測試用例，輸出一行包含 Case #x: y，其中 x 是測試用例編號（從 1 開始），y 是 L 形的數量。

## 範例輸入 #1

```
2
4 3
1 0 0
1 0 1
1 0 0
1 1 0
6 4
1 0 0 0
1 0 0 1
1 1 1 1
1 0 1 0
1 0 1 0
1 1 1 0
```

## 範例輸出 #1

```
Case #1: 1
Case #2: 9
```
