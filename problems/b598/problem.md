# b598. Minimize the Number of Coins

## 內容

Suppose there is a world where people use only coins to buy things. In that world, there are four kinds of coins, and all the coins' weight are the same. Today, a lazy man, Bob wants to buy one thing. Because he is so lazy, he does not want to bring any coins when he go home. But he does not want to waste his money too! So, he wants to bring money that exactly equal to the price he needs to pay, and wants to minimum the total number of all coins that he needs to bring. Now write a program to help Bob to know how many coins should he bring in each kind of four coins.

## 輸入說明

Each input contains two lines. The first line has four integers. The four integers denote four different values of the coins, and their values are between 1 and 100. The second line is a integer that denotes the price he needs to pay, and its value is between 1 and 10000. The last line of inputs is only one 0 indicating the end of inputs.

## 輸出說明

For each input data, print out the minimum total number of all coins, and the numbers of each kinds of coins. The first number denotes the total number of all coins; the second number denotes the number of first kind coins; the third number denotes the number of second kind coins; the fourth number denotes the number of third kind coins; the fifth number denotes the number of fourth kind coins.


If there are more than one possible answer, minimize the number of the first kind coins. If the number of the first kind coins is also the same, output the answer whose number of the second kind coins is smaller. For example, if the minimum total number is 9, and three possible answers are: 1 1 4 3, 2 0 0 7 and 1 2 3 3. Then your answer should be 9 1 1 4 3. Furthermore, if the answer is not possible without wasting money, just print 0.

## 範例輸入 #1

```
4 3 2 1
10
2 5 7 3
10
25 5 10 15
33
17 10 7 3
22
0
```

## 範例輸出 #1

```
3 1 2 0 0
2 0 0 1 1
0
5 0 1 0 4
```
