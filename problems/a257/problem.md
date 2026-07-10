# a257. NCPC2011 Problem K Key Persons

## 內容

Problem K

  Key Persons

  Input File: pk.in

  Time Limit: 3 seconds

  There is a secret club, named No-Communication-Permitted-Club (NCPC), 
 formed by n college students and every student has a unique ID which is a 
 positive integer. Two students can talk if and only if their ID have a common
 factor bigger than 1. For convenience, we use the ID to represent the students.
 Two students p and q are “relevant” if either they can talk or they can communicate 
indirectly via other students. Otherwise they are “non-relevant”.

          Hence, two students p and q are relevant if either p and q have a common
 factor bigger than 1 or there is a sequence of integers (a1 = p, a2,…, ak = q)
 in S such that ai and ai+1 for 1 ≦ i ≦ k-1 have a common factor bigger
 than 1, where S is the setoff all ID of the students. The club needs to elect
 some “key persons” to manage the club. A student x in S is a key person if
 after excluding x from S, it can cause two relevant students p ∈S and q ∈S, 
 become non-relevant in S’ = S – x.

          For example, consider S = (1,2,3,4,5,6,7,8,9). Then, 2 and 9 is relevant
 because sequence (2,6,9) exists, where 2 and 6 have a common factor 2
 (>1) and 6 and 9 have a common factor 3(>1). However, after excluding 6
 from S, 2 and 9 becomes non-relevant in the resulting set S’ = S – 6 =
 {1,2,3,4,5,6,7,8,9}. Hence, 6 is a key person.

          Given a set club members S, your task is to write a computer program to conpute the number of key persons in S.

   

  Technical Specification

     All ID are integers at least one and at most 30000 and the number of
 students in each test case is no more than 1000.

## 輸入說明

The first line of the input file contains an integer, denoting the number if
 test cases to follow. For each test case, the club S = {a1, a2, ... , an} is given
 with the following format : The first line contains a positive integer n. In the
 following n lines, each line represents one integer in S such that an integer in
 the ith line represents ai .

## 輸出說明

For each test case, output the number of key persons in S.

## 範例輸入 #1

```
2
8
2
4
6
8
10
12
14
16
10
1
2
3
4
5
6
7
8
9
10
```

## 範例輸出 #1

```
0
2
```
