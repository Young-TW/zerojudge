# b773. 50011. Spell Checker

## 內容

Write a simple spell checker. First you will read a set of words as a dictionary. Next you will read a set of word as text. For example our dictionary has apple, apples, orange, banana. All words are in lower case from 'a' to 'z' only.


For every word in text you must look up the dictionary and determine if the spelling is correct. If the word from text is in the dictionary, like apple, then you output a line >apple.


If the word from text is not in the dictionary, you must list all possible candidates as ?apple apples, in the order they appear in the dictionary. A word in the dictionary is a candidate if one of the following is true.


- If we replace a character in the candidate, it becomes the word in text. Note that we can only change one character, so apple is not a candidate of aqqle.
- If we add a character into the candidate, it becomes the the word in text. Note that a character could be removed from every possible position, so apple is a candidate of appple.
- If we remove a character from the candidate, it becomes the word in text. Note that a character could be added into every possible position, so apple is a candidate of aple.

If you cannot find any candidate, simply output !aple.

## 輸入說明

The first line contains an integer $N$ denoting the number of words in the dictionary. Followed by $N$ lines, each line contains a word $w_i$ denoting the $i$-th word in the dictionary. After $N+1$ lines, the next line contains an integer $Q$ denoting the number of words in text. Followed by $Q$ lines, each line contains a word $q_i$ denoting the $i$-th word in text.


- $N \le 200, ; \sum |w_i| \le 10000, ; |w_i| \le 100, ; Q \le 20, ; |q_i| \le 20 $ for 95% testdata.
- $N \le 100000, ; \sum |w_i| \le 1000000, ; |w_i| \le 100, ; Q \le 1000, ; |q_i| \le 100 $ for 100% testdata.

## 範例輸入 #1

```
5
case
content
contest
common
onganize
4
cases
common
context
come
```

## 範例輸出 #1

```
?case
>common
?content contest
!come
```
