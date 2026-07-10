# d421. 00332 - Rational Numbers from Repeating Fractions

## 內容

Now if we let X be the original number (7/22), we can compute the numerator and denominator of the expression


 



![image](ShowImage?id=288)


 


For 
![image](ShowImage?id=289)
 we obtain the following calculation for the numerator of this fraction:


 



![image](ShowImage?id=290)


 


The denominator is just 1000 - 10, or 990. It is important to note that the expression in the numerator and the denominator of this expression will always yield integer values, and these represent the numerator and denominator of the rational number. Thus the repeated fraction 
![image](ShowImage?id=291)
 is the decimal expansion of the rational number 315/990. Properly reduced, this fraction is (as expected) just 7/22.

## 輸入說明

輸入包含好幾行測試資料


每行的第 1 個數字代表 j


接著一個空白


然後是 0.ddddd…（d 代表一個十進位的數字, 最多有 9 個 d，也就是說 k+j 最大可為 9，注意：j 有可能為0，代表不是循環小數）


j=-1 代表輸入結束

## 輸出說明

對每一行輸入資料


輸出第幾個 Case


然後輸出其有理數的表示法 p/q（需約分）


見 Sample output

## 範例輸入 #1

```
2 0.318
1 0.3
2 0.09
6 0.714285
-1
```

## 範例輸出 #1

```
Case 1: 7/22
Case 2: 1/3
Case 3: 1/11
Case 4: 5/7
```
