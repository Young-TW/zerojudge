# e581. 11067 - Little Red Riding Hood

## 內容

你們可能都知道小紅帽的童話故事，以及她想去看望祖母的方式，但是在途中遇到了一隻狼，最後被狼吃掉了，最後被一位勇敢的獵人救了出來。
現在，如果"小紅帽"最初沒有遇到過狼，她將避免很多麻煩(她不會被狼吃掉，勇敢的獵人也不必解救她)。
她首先遇到了狼，部分原因是因為她缺乏信息。她只是不知道在哪裡可能遇見狼。
連接小紅帽的房子和她祖母的房子的道路網是矩形網格。小紅帽的房子位於網格的左下角，祖母的房子位於網格的右上角。
數學上特別聰明的小紅帽總是想以最短的路線去見祖母。這意味著小紅帽只能在網格上"向右"或"向上"移動。這樣可以確保她始終使用最短的路線。
現在，如果她提前知道了狼的可能位置，那麼她會選擇一條不與狼相遇的路徑。
現在給定地圖的大小和狼的可能位置(特別的是，狼只能在網格的交叉點遇到小紅帽)。
請計算在小紅帽的限制下，從小紅帽的房子走到祖母的房子的可能路徑數(只能向右和向上移動而且不能遇到狼)。



![image](ShowImage?id=4054)

## 輸入說明

有多組測資。
每組測資第一行有兩個整數w、h (1 ≤ w,h ≤ 100)，w代表地圖的寬度，h代表地圖的高度。
如果w = h = 0代表輸入結束。
接下來下一行有一個整數n (0 ≤ n ≤ 100)，n表示有幾處狼可能出現的位置。
接下來n行每行包含兩個整數x、y (0 ≤ x,y ≤ 100)。代表狼所在的座標。
小紅帽的房子座標為(0, 0)，奶奶的房子座標為(w, h)。狼不能在任何一個房子裡。

## 輸出說明

對於每組測資，輸出從小紅帽的房子走到祖母的房子的可能路徑數。
如果可能路徑數有X條(X > 1)
輸出"There are X paths from Little Red Riding Hood's house to her grandmother's house."
如果可能路徑數只有1條
輸出"There is one path from Little Red Riding Hood's house to her grandmother's house."
如果沒路可走
輸出"There is no path."
可能路徑數 ≤ 2^32 - 1。

## 範例輸入 #1

```
1 1
0
1 1
2
0 1
1 0
4 4
3
0 1
1 1
3 1
10 10
0
10 10
3
0 1
1 1
1 0
3 3
5
1 0
1 1
1 2
2 2
3 2
0 0
```

## 範例輸出 #1

```
There are 2 paths from Little Red Riding Hood's house to her grandmother's house.
There is no path.
There are 7 paths from Little Red Riding Hood's house to her grandmother's house.
There are 184756 paths from Little Red Riding Hood's house to her grandmother's house.
There is no path.
There is one path from Little Red Riding Hood's house to her grandmother's house.
```
