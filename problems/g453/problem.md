# g453. 11258: String Partition

## 內容

John was absurdly busy for preparing a programming contest recently. He wanted to create a ridiculously easy problem for the contest. His problem was not only easy, but also boring: Given a list of non-negative integers, what is the sum of them? However, he made a very typical mistake when he wrote a program to generate the input data for his problem. He forgot to print out spaces to separate the list of integers. John quickly realized his mistake after looking at the generated input file because each line is simply a string of digits instead of a list of integers. He then got a better idea to make his problem a little more interesting: There are many ways to split a string of digits into a list of non-zero-leading (0 itself is allowed) 32-bit signed integers. What is the maximum sum of the resultant integers if the string is split appropriately?

## 輸入說明

The input begins with an integer N $(\leq 500)$ which indicates the number of test cases followed. Each of the following test cases consists of a string of at most 200 digits.

## 輸出說明

For each input, print out required answer in a single line.

## 範例輸入 #1

```
6
1234554321
5432112345
000
121212121212
2147483648
11111111111111111111111111111111111111111111111111111
```

## 範例輸出 #1

```
1234554321
543211239
0
2121212124
214748372
5555555666
```
