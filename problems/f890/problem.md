# f890. DD的族譜

## 內容

DD人物介紹 : https://zerojudge.tw/ShowProblem?problemid=f754 


DD在這疫情嚴峻的時間裡，因為沒朋友想和他視訊聊天，於是他無聊時便在家裡亂翻家裡的東西，他無意間翻到家裡的一卷族譜，但他看不太懂字，於是便問他爸這是什麼，爸爸便跟他解釋什麼是族譜，並將每一條血緣或姻親關係告訴他，DD藉由一條條的關係也自己畫出了一個族譜，爸爸看DD很閒，便給他一項任務，告訴他家裡每個人的關係，希望DD能將每個人的年紀大小排出順序。


  以下是一些簡單的規則：


1.長輩一定比晚輩大(不用考慮因太晚生或太早生造成晚輩年紀比長輩大)


2.哥哥姊姊比弟弟妹妹大


3.若同輩間分不出來誰大誰小，年齡由D最大，接著年齡由大而小依序為：A、B、C、E、F……W、X、Y、Z


4.一個人不會跨輩分


  不過，爸爸油時也會拿錯誤的族譜考DD，請DD分辨出來，以下是幾種錯誤狀況：


1.輩分混亂(e.g.A是B的爸爸，B是C的爸爸，C是A的女兒)


2.年齡混亂(e.g.A是B的哥哥，C是B的妹妹，C是A的姐姐)


3.性別混亂(e.g.A是B的媽媽，A是C的阿公)


  不用考慮以下幾種錯誤:


1.稱謂不一樣(e.g.A是B的哥哥，C是A的爸爸，C是B的叔叔)


2.有可能出現同性婚姻或一個人有多個伴侶


3.除輩分、年齡與性別混亂，其他一律不考慮

## 輸入說明

第一行有兩數字N、M，代表有幾人與幾行輸入(0<N≦26，0<M≦30)


接著有M行，每行有兩字元C1、C2及一字串S，代表C1是C2的S


C1、C2為第一個(A)到第N個大寫字母。


S只可能為 : father、mother、parent、son、daughter、child、grandpa、grandma、grandparent、grandson、granddaughter、grandchild、older brother、older sister、younger brother、younger sister、brother、sister、cousin、uncle、aunt、nephew、niece、husband、wife


以上若有單字看不懂，請詢問google。


若沒指出性別(e.g.child、parent)，則都有可能。


第一到第N個字母都一定會出現在輸入中至少一次，且全部人都會有關聯。(不會有人獨立和其他人沒關係，也不會有兩群彼此沒關聯)

## 輸出說明

輸出有若干行，依序照輩分輸出，最大輩分的人輸出在第一行，第二大輩分的人輸出在第二行，以此類推。


每行依照年齡由大到小輸出，若年齡不一定，請參照上述規則第3點。


若輸入是錯誤的情況，請輸出，"DD被整了!"

## 範例輸入 #1

```
4 3
A B father
C B brother
D B sister
```

## 範例輸出 #1

```
A
D B C
```

## 範例輸入 #2

```
6 5
A B mother 
B C sister
D E grandson
C D big brother
E F wife

```

## 範例輸出 #2

```
E F
A
C D B
```

## 範例輸入 #3

```
3 3
A B husband
B C child
C A grandson
```

## 範例輸出 #3

```
DD被整了!
```
