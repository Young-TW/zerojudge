# f470. 12333 Revenge of Fibonacci

## 內容

uva 12333 - Revenge of Fibonacci 原題連結


The well-known Fibonacci sequence is defined as following:
F(0) = F(1) = 1
F(n) = F(n-1) + F(n-2) ,for n>=2
Here we regard n as the index of the Fibonacci number F(n).
This sequence has been studied since the publication of Fibonacci’s book Liber Abaci. 
So far, many properties of this sequence have been introduced.
You had been interested in this sequence, while after reading lots of papers about it. 
You think there’s no need to research in it anymore because of the lack of its unrevealed properties. 
Yesterday, you decided to study some other sequences like Lucas sequence instead.
Fibonacci came into your dream last night. “Stupid human beings. Lots of important properties 
of Fibonacci sequence have not been studied by anyone, for example, from the Fibonacci number 
347746739...”
You woke up and couldn’t remember the whole number except the first few digits Fibonacci told you. 
You decided to write a program to find this number out in order to continue your research on Fibonacci sequence.
眾所周知的斐波那契數列定義如下：
F（0）= F（1）= 1
F（n）= F（n-1）+ F（n-2），對於n> = 2
在這裡，我們將n視為斐波那契數F(n)的索引值。
斐波那契數列自從 Liber Abaci(計算之書) 著作出版以來，就一直被研究著。
到目前為止，已經介紹了該序列的許多屬性。
在閱讀了大量有關此序列的文章之後，您對這個序列很感興趣。
您認為由於缺少其未公開的屬性，因此不再需要對其進行研究。
昨天，您決定研究其他一些序列，例如Lucas序列。
昨晚斐波那契進入您的夢中。 “愚蠢的人。很多斐波那契數列重要的屬性
任何人都尚未研究過，例如從斐波那契數347746739 ...”
您醒來了，除了斐波那契告訴您的前幾位數之外，您已經忘記了整個號碼。
您決定編寫一個程序來找出該數字，以便繼續進行斐波那契數列的研究。
=========== 題目內容簡要說明 ========================
 給一個數字開頭1~40位，求最早出現有此開頭的Fibonacci數字的索引值，索引值從0開始。
比如 開頭5,最早有5開頭的是f(4):5、開頭9,f(15):987是最先出現的、開頭12,f(25):121393是最先出現的。
如果沒任何Fibonacci數字包含所給的開頭, 則輸出-1。索引值上限小於100000、每個數字開頭最多40位數。

## 輸入說明

There are multiple test cases. The first line of input contains a single integer T denoting the number of test cases (T <= 50000). 
 For each test case, there is a single line containing one non-empty string made up of at most 40 digits. 
 And there won’t be any unnecessary leading zeroes. 
有多個測試用例。 輸入的第一行包含一個單個整數T，表示測試用例的數量（T <= 50000）。
對於每個測試用例，只有一行包含一個最多由40位數字組成的非空字符串。 而且不會有任何不必要的前導零。

## 輸出說明

For each test case, output the smallest index of the smallest Fibonacci number whose decimal notation
begins with the given digits. If no Fibonacci number with index smaller than 100000 satisfy that
condition, output ‘-1’ instead — you think what Fibonacci wants to told you beyonds your ability.
對於每個測試用例，輸出最小斐波納契數的最小索引，其小數點表示法
以給定的數字開頭。 如果沒有索引小於100000的斐波那契數滿足
條件下，改為輸出“ -1”-您認為斐波那契想要告訴您的內容超出了您的能力範圍。

## 範例輸入 #1

```
15
1
12
123
1234
12345
9
98
987
9876
98765
89
32
51075176167176176176
347746739
5610
```

## 範例輸出 #1

```
Case #1: 0
Case #2: 25
Case #3: 226
Case #4: 1628
Case #5: 49516
Case #6: 15
Case #7: 15
Case #8: 15
Case #9: 43764
Case #10: 49750
Case #11: 10
Case #12: 51
Case #13: -1
Case #14: 1233
Case #15: 22374
```
