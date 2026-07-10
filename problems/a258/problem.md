# a258. NCPC2011 Problem F Inverse Affine Transform

## 內容

Problem F

  Inverse Affine Transform

  Input File: pf.in

  Time Limit: 3 seconds

          Let m be a positive integer, under a modular arithmetic, an affine transform 
 on the set S = {0,1,2,…,m-1} can be defined as

                                                  y ≡ ax+b  mod  m                               (1)

  Some permutations on an integer set S could be implemented based on the
 above affine transform with parameters a and m being relatively prime, that
 is, their greatest common divisor gcd(a,m) = 1. If gcd(a, m) = 1, the inverse
 transform exists which is also an affine transform, say,

                                                  x ≡ cy+d  mod  m                               (2)

          This problem asks you to write a program to dectect and compute the
 inverse transform of an affine transform with the given parameters m, a, b.

## 輸入說明

The first line of the input file always contains one integer K indicating the
 number of test cases to come. Each test data set consists of a line of three
 positive integers m, a, b, respectively. Note that 3 ≦ K ≦ 5 and m ≦　220 = 
 10485676 in this problem.

## 輸出說明

K lines, each line consist of “No inverse, gcd(a,m)=” followed by the value
 gcd(a,m) if gcd(a,m) > 1 or the values of c and d, where 0 < c, d < m, if
 gcd(a,m) = 1

## 範例輸入 #1

```
5
5 2 1
16 6 5
262144 13131 128
1048576 2004 8000
1048576 301 100
```

## 範例輸出 #1

```
3 2
No inverse, gcd(a,m)=2
15971 52864
No inverse, gcd(a,m)=4
456357 501644
```
