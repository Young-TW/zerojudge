# c099. 00115 - Climbing Trees

## 內容

這個問題的目地在討論兩個人在所謂的「家庭樹」（family tree 即族譜）裡，他們的關係為何。給你兩組名字：第一組裡有若干對名字，就是所謂的「孩子，家長 對」（child-parent pairs），也就是一對名字，前面的名字是孩子的名字，而後面的名字為其家長的名字；第二組則也有若干對名字，是「欲查詢 對」（query pairs），其表達格式跟前面的「孩子，家長 對」一樣有兩個名字。給你這兩組若干對的名字，你必須寫個程式來判斷在「欲查詢 對」裡，每對的那兩個人彼此關係為何。在這裡我們設定一個人只會有一個家長（雖然我們都知道每個人都有父、母親二者，但是在本問題中，我們僅以其中一人代表）


在此問題裡，我們說「孩子，家長 對」p、q 表示 p 是 q 的孩子。我們為了要表示出所謂的關係，我們先看下面的定義：


- 當在輸入檔案的「孩子，家長 對」裡有 p q （或者 q p），我們說 p 是 q 的 0 級子孫 （或者 0 級祖先）
- 當在輸入檔案的「孩子，家長 對」裡有 p r （或者 q r），而且 r 是 q 的 (k-1) 級子孫（或者 p 是 r 的 (k-1) 級祖先），則稱 p 是 q 的 k 級子孫 （或者 k 級祖先）

在這個問題裡，任兩個人 p , q 之間的關係一定可歸類到下列四種的其中之一（如果他們有關係的話）


- 直系子孫類（child）： child、grand child、great grand child、great great grand child，依此類推。（即：孩子、孫子、曾孫、曾曾孫 ...）
根據定義，當輸入檔案裡的「孩子，家長 對」有 p q 存在（也就是 p 是 q 的 0 級子孫），則這時 p 是 q 的「child」─即是「孩子」；而當 p 是 q 的 1 級子孫時，我們就稱 p 是 q 的「grand child」─即是「孫子」；當 p 是 q 的 (n+1) 級子孫，則 p 是 q 的「great great ... great grand child」，其中有 n 個 " great "，然後後面接 " grand child "，也就是「曾曾...曾孫」的意思（其中有 p 個 " 曾 " ）。


 



- 直系長輩類（parent）： parent、grand parent、great grand parent、great great grand parent，依此類推。（即：父（母）、祖父（母）、曾祖父（母）、曾曾祖父（母））
 （注意：無論是男是女，每一個人如果有家長，則必然是恰有一個）
根據定義，當輸入檔案裡的「孩子，家長 對」有 q p 存在（也就是 p 是 q 的 0 級祖先），則這時 p 是 q 的「parent」─即是「父（母）」；而當 p 是 q 的 1 級祖先時，我們就稱 p 是 q 的「grand parent」─即是「祖父（母）」；當 p 是 q 的 (n+1) 級祖先，則 p 是 q 的「great great ... great grand parent」，其中有 n 個 " great "，然後後面接 " grand parent "，也就是「曾曾...曾祖父（母）」的意思（其中有 p 個 " 曾 " ）。


 



- 旁系血親類（就是非直系的遠親）（ cousin ）：
 依兩個人對其同祖先的輩分差距，可分為 0th cousin、 1st cousin、 2nd cousin，依此類推；對於兩個人彼此的輩分差距又可分為 once removed、twice removed、three times removed，依此類推。（ removed 有類似親等遠近關係之意）
根據定義，只要 p 和 q 有血緣關係，而且他們不是直系血親關係，那他們就是旁系血親的關係。（或者也可以這樣講，如果把 family tree 當作是一個無向圖，則存在一條路徑連通 p 與 q）今天將 p 和 q 的共同祖先裡，輩份最小的稱作 r （也就是 r 的子孫裡沒有人既是 p 的祖先，又是 q 的祖先。），然後知道 p 是 r 的 m 級子孫， q 是 r 的 n 級子孫。


則我們這樣定義：p 和 q 的關係有 '' kth cousins ''，其中 k=min(n,m)（也就是 k 是 p , q 裡面較小的那一個）；而且 p 和 q 的關係還有 '' cousins removed j times '' ，其中 j=| n-m|（也就是 j 為 n 和 m 差的絕對值。）


 



- 兄弟姊妹類（sibling）： 0th cousins removed 0 times 就是所謂的「兄弟姊妹」。（也就是他們有同一個家長）

## 輸入說明

輸入包括2個部分：第一部部分為「孩子，家長 對」，每對一列。包含孩子和家長的名字，名字由小寫字母及.組成。若遇到孩子的名字為 no.child 代表這部分的輸入結束。注意 ，" no.child " 開頭的這一對名字本身並不算在「孩子，家長 對」裡，它的作用只是拿來分隔「孩子，家長 對」和「欲查詢對」而已。另外，這部分的輸入也不會含有循環矛盾的關係，也就是不會有人既是另一人的子孫又是其祖先。


接著就是「欲查詢對」，其格式與第一組一樣，都是每列兩個名字，由小寫字母或句號組成，中間用一個以上的空白隔開。而「欲查詢對」是以 end-of-file 作結尾。


在輸入中，不同的名字不會超過 300 個。每個名字皆不超過 31 個字母長。「欲查詢對」裡最多不會超過 100 對名字。請參考Sample Input。

## 輸出說明

對於查詢對裡的每對名字 p q，都必須輸出 p 是 q的什麼關係──用下面的格式：


- child, grand child, great grand child, great great ...great grand child
- parent, grand parent, great grand parent, great great ...great grand parent
- sibling
- n cousin removed m
- no relation

其中第四項，如果是 " n-cousin is removed 0 times " 則只需輸出 n cousin 即可。也就是說不能輸出 removed 0 這個東西。另外，不要在數字的後面加上 st, nd, rd, th 等字樣。請參考Sample Output。

## 範例輸入 #1

```
alonzo.church oswald.veblen
stephen.kleene alonzo.church
dana.scott alonzo.church
martin.davis alonzo.church
pat.fischer hartley.rogers
mike.paterson david.park
dennis.ritchie pat.fischer
hartley.rogers alonzo.church
les.valiant mike.paterson
bob.constable stephen.kleene
david.park hartley.rogers
no.child no.parent
stephen.kleene bob.constable
hartley.rogers stephen.kleene
les.valiant alonzo.church
les.valiant dennis.ritchie
dennis.ritchie les.valiant
pat.fischer michael.rabin
mike.paterson dennis.ritchie
```

## 範例輸出 #1

```
parent
sibling
great great grand child
1 cousin removed 1
1 cousin removed 1
no relation
1 cousin
```
