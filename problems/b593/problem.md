# b593. Code

## 內容

Transmitting and memorizing information is a task that requires different coding systems for the best use of the available space. A well-known system is that one where a number is associated to a character sequence. It is considered that the words are made only of lower case letters of English alphabet a, b, c, . . . , z (26 characters). Assume that we consider the words in which each letter is used at most once. The coding system works like this:


- 
For a n-letter word w = w1w2 . . . wn, here wi denotes a letter for i = 1, 2, . . . , n, the letter wi = wj for all i = j and the order of wi precedes the order of wj in alphabetical order if i < j.



- The words are arranged in the increasing order of their length.

- The words with the same length are arranged in lexicographical order.
- 
We code these words by integers, starting with a. Hence, these words are coded as follows: a -> 1, b -> 2, . . ., z -> 26, ab -> 27, . . ., az -> 51, bc -> 52, . . ., vwxyz -> 83681, . . ., and so no.




Write a program to specify the number for a given word if it can be coded according to this coding system.

## 輸入說明

The input data consists of several test cases. Each test case has one line that contains a word. The word has the following constraints:


- The maximum length of a word is 26.

- The word only uses 26 characters of English alphabet.

The number 0 indicates the end of the input data.

## 輸出說明

The output of each test case should be in one line. The output contains the code of the given word, or 0 if the word cannot be coded.

## 範例輸入 #1

```
bf 
abca 
vwxyz 
0
```

## 範例輸出 #1

```
55 
0
83681 
```
