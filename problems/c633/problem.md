# c633. 基礎排序 #2-2 ( 質因數和 )

## 內容

測資中有若干行字串 S
S 為大小寫字母及數字的混和。
例： 
S1 = dMB1WA2rjoiy8 , 可取出文字字串 T = dMBWArjoiy , 數字 N = 128 , N 的質因數和為 2 
S2 = dMB1WA2rjoiy6 , 可取出文字字串 T = dMBWArjoiy , 數字 N = 126 , N 的質因數和為 12 (2,3,7) 
請將測資中的字串排序後輸出。
規則如下：
1)  依質因數和遞減排序。
2)  質因數和相同則對 T 做遞增排序。
3)  T 也相同則對 N 做遞減排序。

## 範例輸入 #1

```
dMB1WA2rjoiy8
dMB1WA2rjoiy6
```

## 範例輸出 #1

```
dMB1WA2rjoiy6
dMB1WA2rjoiy8
```
