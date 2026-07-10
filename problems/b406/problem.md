# b406. 12538 - Version Controlled IDE

## 內容

Programmers use version control systems to manage files in their projects, but in these systems, versions are saved only when you manually submit. Can you implement an IDE that automatically saves a new version whenever you insert or delete a string?
Positions in the buffer are numbered from 1 from left to right. Initially, the buffer is empty and in version 0. Then you can execute 3 commands (vnow means the version before executing the command, and L[v] means the length of buffer at version v):
 1 p s: insert string s after position p (0<=p<=L[vnow], p = 0 means insert before the start of the start of the buffer). s contains at most 1 and at most 100 letters.
 2 p c: remove c characters starting at position p (p>=1; p + c<=L[vnow] + 1). The remaining characters (if any) will be shifted left, filling the blank.
 3 v p c: print c characters starting at position p (p>=1; p + c<=L[v] + 1), in version v (1<=v<=vnow).
The first command is guaranteed to be command 1(insert). After executing each command 1 or 2, version is incremented by 1.

## 輸入說明

There is only one test case. It begins with a single integer n (1<=n<=50,000), the number of commands.
Each of the following n lines contains a command. The total length of all inserted string will not exceed 1,000,000.
In order to prevent you from preprocessing the command, we adopt the following obfuscation scheme:
 Each type-1 command becomes 1 p + d s
 Each type-2 command becomes 2 p + d c + d
 Each type-3 command becomes 3 v + d p + d c + d
Where d is the number of lowercase letter `c' you printed, before processing this command.
Before the obfuscation, the sample input would be: 
6
1 0 abcdefgh
2 4 3
3 1 2 5
3 2 2 3
1 2 xy
3 3 2 4

## 輸出說明

Print the results of command 3, in order. The total length of all printed strings will not exceed 200,000.

## 範例輸入 #1

```
6
1 0 abcdefgh
2 4 3
3 1 2 5
3 3 3 4
1 4 xy
3 5 4 6
```

## 範例輸出 #1

```
bcdef
bcg
bxyc
```
