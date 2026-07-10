# a868. 8. St. Ives

## 內容

有一句傳統的英文迷語是這樣的 :

" 當我正想去聖艾夫斯時，

我遇到了一個男人與七個妻子，

每個妻子有七個袋子，

每個袋子裡有七隻貓，

每隻貓有七個小貓，

小貓，貓，袋子，和妻子，

有多少人有去聖艾夫斯？"

 
答案當然是1。解決一個這樣的謎語需要的人工智慧超越本次比賽的範圍，相反的，讓我們留下這個謎語給人類，然後寫出一個可以輸入像聖艾夫斯謎語格式的程式，並做一些基本的數學運算吧！

## 輸入說明

程式的輸入格式是像下列這樣的五行:

A MAN WITH NUMBER COMPANIONS 

EACH COMPANION HAD NUMBER CONTAINERS 

EACH CONTAINER HAD NUMBER OBJECTS 

EACH OBJECT HAD NUMBER ITEMS 

HOW MANY SOMETHINGS? 

有效的數字為2到13(包含)，這些數字不一定相等。單數或複數的差別只在於字尾的S，即使它不符合英文的拼字規則(例如 WIFES而不是WIVES)。"SOMETHINGS"可能是"COMPANIONS" "CONTAINERS " "OBJECTS " 或"ITEMS " 。

## 輸出說明

你的程式需要輸出"SOMETHINGS"的數量和"SOMETHINGS"的複數形。

## 範例輸入 #1

```
A MAN HAD FIVE EMPLOYEES 
EACH EMPLOYEE HAD NINE PROJECTS 
EACH PROJECT HAD SEVEN DEADLINES 
EACH DEADLINE HAD THIRTEEN IMPEDIMENTS 
HOW MANY DEADLINES? 
```

## 範例輸出 #1

```
315 DEADLINES
```
