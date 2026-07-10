# b309. 聖杯戰爭

## 內容

聖杯-傳說中可以實現任何願望的寶物，每隔一段時間會出現在世界上，並且會選定七位魔法師參與爭奪聖杯的競爭，稱為「聖杯戰爭」。在「聖杯戰爭」獲勝的人，就可以得到聖杯並實現願望。
 
今年30歲的你，因為達成了某些條件而成為了魔法師，並且得到了參與聖杯戰爭的資格。每一個參加者(Master)都可以召喚一位英靈成為自己的Servant，Servant分為七個職階，分別為Saber、Lancer、Archer、Rider、Caster、Assassin、Berserker。身為Master的你，第一件事當然要選擇你的Servant，如果在召喚Servant之前被其他魔法師襲擊就不好了。
剛好你在你家發現了一本疑似是魔法書的東西，書上寫著一堆你看不懂的內容，你決定用這本書來決定你要選擇哪個Servant。你決定將每一個英文字母(不分大小寫)都對應到一個Servant。
A-Saber
B-Lancer
C-Archer
D-Rider
E-Caster
F-Assassin
G-Berserker
H-Saber
I-Lancer
J-Archer
以此類推
每當書中出現一個英文字母(非字母則無視)，相對應的Servant在你心中的分數就會+1，最後分數最高的就決定是你的Servant了!

## 輸入說明

書的內容為一堆字元(不超過10,000,000個)，以EOF結尾。

## 輸出說明

輸出最高分的Servant，若有同分的狀況則輸出Saber、Lancer、Archer、Rider、Caster、Assassin、Berserker中順序較前面的。

## 範例輸入 #1

```
I'm a master.
You are my servant.
```

## 範例輸出 #1

```
Saber
```
