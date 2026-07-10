# b185. 6. 按鈕問題

## 內容

給一個n x m的方格(1<=n<=6，1<=m<=6)，O代表突起的按鈕，X代表已壓下的，當你按下一個按鈕，它周圍的四個按鈕的狀態也會同時改變。請問你要讓所有的按鈕變成壓下的狀態，至少要按幾次按鈕。

![image](images/problems/b185.gif)

## 輸入說明

第一列有兩個正整數n及m (1<=n<=6，1<=m<=6)，代表為n x m大小的方格，接著會有n行，每一行有m筆數據。

## 輸出說明

對每一筆測試資料，使用以下格式輸出一行表示完成所需的最小按鈕次數：

Minimum Steps : n，n表示所需最小按鈕次數。

如果無論如何無法達成目標，則輸出：Can not

## 範例輸入 #1

```
2 2
OO
OO
1 2
OX
6 6
XXXXXX
XXXOXX
XXOOOX
XOXOXX
OOOXXX
XOXXXX
```

## 範例輸出 #1

```
Minimum Steps :4
Can not
Minimum Steps :2
```
