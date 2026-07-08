# b605. Package

## 內容

A store sells seven kinds of products. All products' height are the same, and each product's length is equal to it's width. The seven kinds of products' length are: 1, 2, 4, 8, 16, 32, 64. Suppose a man bought some products and he wants to pack all the things he bought in only one box. He may buy the same products more than one. The box's height is equal to all products', and the box's length is equal to it's width. A bigger box costs more than a smaller one! Your task is to write a program to help the man to find the minimum length of the box he needs.

## 輸入說明

Each input contains one line which has seven integers. Each integer denotes the number of the same kind products that the man bought. The first integer is the number of all products whose length are 1; the second is the number of all products whose length are 2; the third is the number of all products whose length are 4; . . .; the seventh is the number of all products whose length are 64. Each input value is between 0 and 5000. The last line of inputs is only one -1 indicating the end of inputs.

## 輸出說明

For each input data, print out the minimum length of the box that the man could use it to pack all the products.

## 範例輸入 #1

```
1 0 0 0 0 0 0
1 1 1 1 0 0 0
0 0 0 0 20 0 1
0 0 0 1 20 0 1
-1
```

## 範例輸出 #1

```
1
12
96
104
```
