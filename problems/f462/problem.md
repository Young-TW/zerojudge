# f462. Shortst Names

## 內容

uva 12506 Shortst Names    原題連結
In a strange village, people have very long names. For example: aaaaa, bbb and abababab.
在一個奇特的村莊里，人們名字很長。 例如：aaaaa，bbb和abababab。
You see, it’s very inconvenient to call a person, so people invented a good way: just call a prefix of the names. 
您會發現，喊叫別人名字時很不方便，所以人們發明了一種好方法：只需給名字加上一個前綴即可。 
For example, if you want to call ‘aaaaa’, you can call ‘aaa’, because no other names start with ‘aaa’. 
例如，如果您想呼叫“ aaaaa”，則可以呼叫“ aaa”，因為沒有其他名稱以“ aaa”開頭。
However, you can’t call ‘a’, because two people’s names start with ‘a’. 
但是，您不能稱呼“ a”，因為兩個人的名字都以“ a”開頭。
The people in the village are smart enough to always call the shortest possible prefix.
村里的人很聰明，總是叫最短的前綴。 
It is guaranteed that no name is a prefix of another name (as a result, no two names can be equal).
確保沒有某人姓名是另一人姓名的前綴（因此，沒有兩個姓名是相同的）。
If someone in the village wants to call every person (including himself/herself) in the village exactly once, 
如果村莊中的某人想對村莊中的每個人（包括他/她自己）都喊一次，
how many characters will he/she use?
他/她將使用多少個字符？


InputThe first line contains T (T<=10), the number of test cases. 
第一行包含T(T<=10)，即測試用例的數量。
Each test case begins with a line of one integer n (1<=n<=1000), the number of people in the village. 
每個測試用例都以一行整數n（1 n 1000）（該村莊的人數）開始。
Each of the following n lines contains a string consisting of lowercase letters, representing the name of a person. 
接下來的n行中的每行包含一個由小寫字母組成的字符串，代表一個人的名字。 
The sum of lengths of all the names in a test case does not exceed 1,000,000.
一個測試用例中所有名稱的長度總和不超過1,000,000。

## 輸入說明

The first line contains T (T<=10), the number of test cases. 
第一行包含T(T<=10)，即測試用例的數量。
Each test case begins with a line of one integer n (1<=n<=1000), the number of people in the village. 
每個測試用例都以一行整數n（1 n 1000）（該村莊的人數）開始。
Each of the following n lines contains a string consisting of lowercase letters, representing the name of a person. 
接下來的n行中的每行包含一個由小寫字母組成的字符串，代表一個人的名字。 
The sum of lengths of all the names in a test case does not exceed 1,000,000.
一個測試用例中所有名稱的長度總和不超過1,000,000。

## 輸出說明

For each test case, print the total number of characters needed.
對於每個測試用例，請印出所需的字符總數。

## 範例輸入 #1

```
3
3
aaaaa
bbb
abababab
10
abc
ac
bbc
bc
cba
ca
def
df
ghk
gk
4
abcd
abd
ad
d
```

## 範例輸出 #1

```
5
20
9
```
