# b770. 47. Play with Words, Too.

## 內容

Write a program (again) to play with words. Your program should support the following commands.


- insert left x n Insert n characters of x at the beginning of a word.
- insert right x n Insert n characters of x at the end of a word.
- insert k x n Insert n characters of x so that the first of them will become the k-th character of this word.
- print
Print the current content of the word in the following format: if the word is "gooooooooooooooooooooooooooogle", you should print "g 1 o 27 g 1 l 1 e 1 $". In other words, you should encode all consecutive sequences with the same character into character-length pairs, then print a dollar sign to indicate the end of the word.

Where x is a alphanumeric character and both n and k are positive integers.


Note that you need to implement this word as a binary tree, otherwise it it very likely that you will run out of time because you need to run through the data structure in order to find the correct location for insertion. You may want to store the number of characters in a node, as well as the number of characters in the subtree to speed thing up.

## 輸入說明

The input data contains a sequence of commands described above. You may assume that all commands are valid. That is, k would not exceed the current length of the word plus 1. The total length of the word would less then 2147483647.

## 輸出說明

You should output the content of the word in the compressed format described above whenever you read the "print" command.

## 範例輸入 #1

```
print
insert left g 2
insert right e 1
insert 3 l 1
insert 2 o 2
print
insert 4 o 25
print
```

## 範例輸出 #1

```
$
g 1 o 2 g 1 l 1 e 1 $
g 1 o 27 g 1 l 1 e 1 $
```
