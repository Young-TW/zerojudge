# d613. Prime Gap

## 內容

The sequence of n - 1  consecutive composite numbers (positive integers that are not prime and not equal to 1) lying between two successive prime numbers p  and p + n  is called a prime gap of length n . For example, 
![image](ShowImage?id=326)
24, 25, 26, 27, 28
![image](ShowImage?id=327)
 between 23 and 29 is a prime gap of length 6.   

 Your mission is to write a program to calculate, for a given positive integer k , the length of the prime gap that contains k . For convenience, the length is considered 0 in case no prime gap contains k .

## 輸入說明

The input is a sequence of lines each of which contains a single positive integer. Each positive integer is greater than 1 and less than or equal to the 100000th prime number, which is 1299709. The end of the input is indicated by a line containing a single zero.

## 輸出說明

The output should be composed of lines each of which contains a single non-negative integer. It is the length of the prime gap that contains the corresponding positive integer in the input if it is a composite number, or `0' otherwise. No other characters should occur in the output.

## 範例輸入 #1

```
10 
11 
27 
2 
492170 
0
```

## 範例輸出 #1

```
4 
0 
6 
0 
114
```
