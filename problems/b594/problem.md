# b594. A Marvelous Pet

## 內容

A marvelous pet, Mark, has a special eating habit. Mark only eats the thing that is lager than the last thing he ate and the sizes of the two things just have a diference of 1. For example, if Mark ate a thing in size k, he only eats the thing in size k + 1 next time.


Suppose Mark needs to eat at least two things. Mark needs to eat the things whose total sizes is equal to n. We note that Mark can only eat the thing whose size is less than n. Suppose that the pet owner, Alice, has n - 1 things whose sizes are from 1 to n - 1. All sizes are integers. Alice wants to know how many possible ways to feed Mark. Write a program to help Alice find the answer.

## 輸入說明

The input contains several test cases. Each test case contains one line. The line contains one integer which denotes the number n. The value of n is between 3 and 1000000.


The last line of input is only one 0 indicating the end of input.

## 輸出說明

For each input data, print how many possible ways that Alice may feed Mark.

## 範例輸入 #1

```
3
4
5
9
25 
0
```

## 範例輸出 #1

```
1
0
1
2
2
```
