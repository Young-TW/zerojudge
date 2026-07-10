# b772. 50010. Word Editor

## 內容

Write a program to edit a word. First you will be given a word consisting of lower letters. Each line afterward is a command. The commands are as follow.


- replace x y
 Both $x$ and $y$ are character. You need to replace all occurrence of $x$ by $y$.
- remove x
 Remove all occurrence of $x$.
- addhead x
 Add a character $x$ at the beginning of the word.
- addtail x
 Add a character $x$ at the end of the word.
- end
 Stop the computation. It is guarantee the last command is always an end.

For example, if you are given a word "pangfeng", then after "replace g d" you will have "pandfend". Then after "remove n" you will have "padfed". After "addhead a" you will have "apadfed". After "addtail s" you will have "apadfeds".

## 輸出說明

It has a testdata set. First line contains a string $S$, then following many commands to edit the word.

* $|S| \le 100000$
* $|\text{#valid command}| \le 100000$
* $|\text{invalid command}| \le 20$

## 範例輸入 #1

```
pangfeng
replace g d
remove n
addhead a
addtail s
end
pangfeng
replace g d
remove n
addhead a
addtail s
addpangfeng b
addhead a
end
```

## 範例輸出 #1

```
apadfeds
invalid command addpangfeng
```
