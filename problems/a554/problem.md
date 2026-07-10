# a554. NCPC PG SHA-4

## 內容

Problem G

  SHA-4

  Input File: pg.in

  Time Limit: 3 seconds

          This is a new hash algorithm invented for NCPC 2012, called SHA4 (simple hash algorithm version 4). Given a message string M, the SHA4 will hash the string into a 160 bits value, called the message digest d.

          d = SHA4(M), where SHA4 is the hash function

          We will give you the SHA4 algorithm and several hashed results of message digests: d0, d1, d2, …. You are to write a program to find the original message M0, M1, M2, …. Such that

          d0 = SHA4(M0), d1 = SHA4(M1), d2 = SHA4(M2), …

          Pseudocode for the SHA4 algorithm is listed in the following:

![image](ShowImage?id=179)

  Note:
 1. All variables are unsigned 32 bists integers.

  2. The input string M is with length 5.

  3. Each input character M[i] is converted into an integer value, by subtracting ASCII value of space from the ASCII value of M[i], that is, the difference between space and the character ASCII value. For example, the space value is 0.

  4. After the value conversion, the five bytes values are stored in word[i], 0 <= i < 5.

   

  Technical Specification

  l   The number of test cases is less the 1024.

  l   All output strings are with length 5.

## 輸入說明

The first line of the input file contains an integer, denoting the number of test cases to follow. For each test case, the message hash digest is given with values of five 32 bits integer in hexadecimal format, each integer separated with at least one space. For example, a sample digest is 0b8414f6 027eeb13 0453edaf 00f93379 002f2d88. All digest values are valid SHA4 outputs.

## 輸出說明

For each test case, output the original message with one line of string, containing only five alphanumeric characters (A-Za-z0-9). For example, you are to output ‘5dogs’ if the input is SHA4(‘5dogs’) = ‘0b8414f6 027eeb13 0453edaf 00f93379 002f2d88’.

## 範例輸入 #1

```
4
0b8414f6 027eeb13 0453edaf 00f93379 002f2d88
0b8419b0 027eec17 0453ef3f 00f933f1 002f2da8
0b8459a5 027efa02 045406ff 00f93981 002f2f10
0b845578 027ef91a 04540577 00f93921 002f2ef8
```

## 範例輸出 #1

```
5dogs
9cats
fade4
cafe8
```
