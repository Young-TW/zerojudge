# b771. 46. Play with Words

## 內容

Write a program to play with words. Your program should support the following commands.


- insert left x Insert character x at the beginning of a word.
- insert right x Insert a character x at the end of a word.
- insert k x Insert character x as the k-th character of this word.
- delete left Delete a character at the beginning of a word.
- delete right Delete a character at the end of a word.
- delete k Delete the k-th character from the word.

Where x is a character other than spaces, and k is a number starting from 1. Initially there is nothing in this word, and after the following command the word should be "bbaac".


commandwordinsert left aainsert left aaainsert left bbaainsert right abaaainsert right cbaaacinsert left bbbaaacdelete rightbbaaainsert 4 cbbacaadelete 5bbacadelete 4bbaainsert 5 cbbaac

## 輸入說明

The input data contains a sequence of commands described above. All commands are valid. For example, if your program receives a "delete 5" command, we ensure that the word would has at least 5 characters for now.

## 輸出說明

After processing the input commands, Your program should find out all of the longest consecutive sequence with the same character from left to right and output the character of each sequence in order, then output the length of the sequences at the end. All data should be separated by a single space.

## 範例輸入 #1

```
insert left a
insert left a
insert left b
insert right a
insert right c
insert left b
delete right
insert 4 c
delete 5
delete 4
insert 5 c
```

## 範例輸出 #1

```
b a 2
```
