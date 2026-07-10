# a459. An Easy Language

## 內容

在克蘇魯神話（Cthulhu Mythos）中，故事敘述著一群古老而邪惡、偉大的存在──舊日支配者，在上古時代曾經統治地球，而如今卻似死亡般地沉睡，其中名為「克蘇魯（Cthulhu）」的神祇，沉睡在南太平洋海底的拉萊耶（R'lyeh）中，當「繁星正點」之時，拉萊耶將從海底浮上，克蘇魯甦醒，重新支配全世界。神話中以一個中心思想貫穿：「在宇宙中，人類的價值毫無意義，並且所有對神秘未知的探求都會招致災難的結局。」而在此神話的神祇們主要被分為四大類：舊日支配者（Great Old Ones）、外神（Outer Gods）、舊神（Elder Gods）和古神（Great Ones）。

          舊日支配者，昔日曾經支配地球且古老而強大的存在，除了「奈亞拉托提普（Nyarlathotep）」之外，如今沉睡在海底、地底深處、或是遙遠的星系中，他們無法自由行動，但是他們可以被咒語召喚到世界上。他們沉睡的原因有二說：最廣為流傳的原因是因為在遠古之時，舊日支配者反叛舊神從而被舊神們囚禁；其次則是他們基於某種原因而選擇沉睡。舊日支配者為遠超凡間之物，見其形象的人都會陷入瘋狂，然而為了獲得其強大的力量，他們被一些外星種族、古代文明或使神秘的宗教團體所崇拜。

  舊日支配者依其元素分為四大陣營：水、火、風、地，其中「水」與「風」敵對，「火」與「地」敵對。例如象徵「水」的存在「沉睡之神」克蘇魯與象徵「風」的存在「無以名狀者（the Unspeakable）」哈斯塔（Hastur）互為死敵；象徵「火」的存在「爆燃者（The Burning One）」克圖格亞（Cthugha）與象徵「地」的存在奈亞拉托提普互為死敵。

          外神，是舊日支配者中幾位特別強大的神的稱呼，他們強大的力量得以影響整個宇宙，以「盲目癡愚之神（Blind Idiot God）」阿薩托斯（Azathoth）──象徵原初宇宙之渾沌──為首，其後有三柱原神「孕育千萬子孫的森之黑山羊（The Black Goat of the Woods with a Thousand Young）」莎布·尼古拉絲（Shub-Niggurath）、「萬物歸一者（The All-in-One）」猶格·索托斯（Yog-Sothoth）、「蠕動之混沌（The Crawling Chaos）」奈亞拉托提普──做為舊日支配者與人類溝通的仲介者──等都是克蘇魯神話中最重要的存在。

          舊神，克蘇魯神話中最為強大的存在，以克塔尼德（Kthanid）為首來對抗舊日支配者和外神。舊神的存在超越了人類的善惡之分，人類難以理解他們的意志，他們一般對人類抱持善意，並協助人類反對舊日支配者，但他們的目的、甚至他們本身對人類都是謎。

  古神，為「地球的孱弱諸神（weak gods of earth）」，他們支配著幻夢境（Dreamlands），並且同受奈亞拉托提普和舊神之一「深淵大帝（Lord of the Great Abyss）」諾登斯（Nodens）保護──儘管他們彼此相互為敵。

          在神話中儘管將他們描述得冷酷、殘忍，但事實上，這些神都是存在的！其實他們都是位在宇宙中某一星系中的星體──無論恆星還是行星，而其中一顆行星的名字便叫作奈亞拉托提普星（Nyarlathotep），行星上有一群類似人類的高等生物，在其行星以及周圍的星球上建立起城市，我們管他叫作奈亞拉托提普星人，但是這個名稱實在是太長不好記，於是住在13區的人們就給了一個簡稱──奈亞子（Nyaruko）。

          儘管奈亞子們發展出來的科技比我們都還要先進，但他們的語言卻異常地簡單！首先，他們在溝通時，接收語言的奈亞子會在大腦中騰出240個空位，這240個空位是連續排成一串，每一個空位都可以寫入一個非負數值，這些數值會在奈亞子大腦的其他部位轉換成對應的字母。

  此外，在接收語言前，奈亞子的注意力會放在第一個空位上，隨著接收到語言的內容，奈亞子的注意力可能會移到下一個空格或是前一個空格，或是改變這些注意空格的數值。記得，注意力不會移出這240個空格外！

  為了方便敘述奈亞子語（Nyaruko language），我們將它與C語言對比，現在我們把大腦的空位當成一個陣列，令Brain[240]，一開始這240格都是空的，另外我們把奈亞子的注意力當作一個整數Ptr，而Ptr一開始為0。以下為奈亞子語對應C語言的語法：

   

     Nyaruko語

      C語言

      說明

      (>OwO)>u~(/OwO)/nya~

      Ptr++

      將注意力移到後一格

      (>OwO)>u~!(/OwO)/nya~!

      Brain[Ptr]++

      注意空格的數值加一

      (>OwO)>u~!!(/OwO)/nya~!!

      Ptr--

      將注意力移到前一格

      (>OwO)>u~!!!(/OwO)/nya~!!!

      Brain[Ptr]--

      注意空格的數值減一

      CHAOS CHAOS!

      While(Brain[Ptr])   {

      若注意空格的數值為零，則跳至下一個對應的「I WANNA CHAOS!」的下一個語句

      I WANNA CHAOS!

      }

      若注意空格的數值為非零，則跳至上一個對應的「CHAOS CHAOS!」的下一個語句

      Let's\(OwO)/nya~

      putchar(Brain[Ptr])

      將注意空格的數值轉為符號

      cosmic!

      Brain[Ptr]=getchar()

      將一個符號轉為數值記入注意空格中

      

          為了簡化問題，我們在此不考慮「cosmic!」語句；每個奈亞子語句間，都會有一至數個空白或是換行，但每個奈亞子語句內的空白是固定的，例如：「CHAOS CHAOS!」之間一定只有一個空白；保證不會有不是上述七個語法之外的語句出現；此外，奈亞子語的符號與數值對應複雜，在此我們使用ASCII碼來代替原本奈亞子語的符號對應關係，因此，我們讓「清空」這個工作即是讓空格的數值設為ASCII碼的0。

          另外，以下是一個簡單的奈亞子語應用範例，好讓更多讀者了解奈亞子語的實際運作方式：

          範例：將注意空格的數值歸0。

          語句：CHAOS CHAOS! (>OwO)>u~!!!(/OwO)/nya~!!! I WANNA CHAOS! 

          C語言等價語法：while ( Brain[ Ptr ] ) Brain[ Ptr ] -- ;

          解說：

  在此語句中，我們可以見到三個語句：「CHAOS CHAOS!」、「(>OwO)>u~!!!(/OwO)/nya~!!!」、「I WANNA CHAOS!」，當「CHAOS CHAOS!」語句執行時，會去檢查注意空格是否為零，如果不是零，則執行「(>OwO)>u~!!!(/OwO)/nya~!!!」將數值減一；若注意空格為零，則跳到對應「I WANNA CHAOS!」的下一個語句（下一語句為空），則注意空格歸零。如果執行到「I WANNA CHAOS!」而注意空格非零，則會跳到上一個對應的「CHAOS CHAOS!」語句的下一個指令（即「(>OwO)>u~!!!(/OwO)/nya~!!!」），如此就像是C語言的迴圈結構。

## 輸入說明

輸入只有一筆奈亞子語的敘述，但如上面所述，可能有一行至多行資料，敘述最尾端以EOF做為結束。測試資料的規定以上面所述為主，此外語句的數量最多不超過1000個。

## 輸出說明

根據語句的內容，輸出對應的符號（如果有要輸出的話，當然有可能為空）。

## 範例輸入 #1

```
(>OwO)>u~(/OwO)/nya~ (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! CHAOS CHAOS! (>OwO)>u~!!(/OwO)/nya~!! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~(/OwO)/nya~ (>OwO)>u~!!!(/OwO)/nya~!!! I WANNA CHAOS! (>OwO)>u~!!(/OwO)/nya~!! 
Let's\(OwO)/nya~ (>OwO)>u~(/OwO)/nya~ (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! CHAOS CHAOS! (>OwO)>u~!!(/OwO)/nya~!! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~(/OwO)/nya~ 
(>OwO)>u~!!!(/OwO)/nya~!!! I WANNA CHAOS! (>OwO)>u~!!(/OwO)/nya~!! (>OwO)>u~!(/OwO)/nya~! 
Let's\(OwO)/nya~ (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
Let's\(OwO)/nya~ Let's\(OwO)/nya~ (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! Let's\(OwO)/nya~ CHAOS CHAOS! (>OwO)>u~!!!(/OwO)/nya~!!! 
I WANNA CHAOS! (>OwO)>u~(/OwO)/nya~ (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! CHAOS CHAOS! (>OwO)>u~!!(/OwO)/nya~!! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~(/OwO)/nya~ (>OwO)>u~!!!(/OwO)/nya~!!! I WANNA CHAOS! (>OwO)>u~!!(/OwO)/nya~!! 
Let's\(OwO)/nya~ (>OwO)>u~(/OwO)/nya~ (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! CHAOS CHAOS! (>OwO)>u~!!(/OwO)/nya~!! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~(/OwO)/nya~ (>OwO)>u~!!!(/OwO)/nya~!!! I WANNA CHAOS! (>OwO)>u~!!(/OwO)/nya~!! 
Let's\(OwO)/nya~ (>OwO)>u~(/OwO)/nya~ (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! CHAOS CHAOS! (>OwO)>u~!!(/OwO)/nya~!! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~(/OwO)/nya~ 
(>OwO)>u~!!!(/OwO)/nya~!!! I WANNA CHAOS! (>OwO)>u~!!(/OwO)/nya~!! Let's\(OwO)/nya~ 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! Let's\(OwO)/nya~ 
(>OwO)>u~!!!(/OwO)/nya~!!! (>OwO)>u~!!!(/OwO)/nya~!!! (>OwO)>u~!!!(/OwO)/nya~!!! (>OwO)>u~!!!(/OwO)/nya~!!! 
(>OwO)>u~!!!(/OwO)/nya~!!! (>OwO)>u~!!!(/OwO)/nya~!!! Let's\(OwO)/nya~ (>OwO)>u~!!!(/OwO)/nya~!!! 
(>OwO)>u~!!!(/OwO)/nya~!!! (>OwO)>u~!!!(/OwO)/nya~!!! (>OwO)>u~!!!(/OwO)/nya~!!! (>OwO)>u~!!!(/OwO)/nya~!!! 
(>OwO)>u~!!!(/OwO)/nya~!!! (>OwO)>u~!!!(/OwO)/nya~!!! (>OwO)>u~!!!(/OwO)/nya~!!! Let's\(OwO)/nya~ 
CHAOS CHAOS! (>OwO)>u~!!!(/OwO)/nya~!!! I WANNA CHAOS! (>OwO)>u~(/OwO)/nya~ 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
CHAOS CHAOS! (>OwO)>u~!!(/OwO)/nya~!! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~(/OwO)/nya~ (>OwO)>u~!!!(/OwO)/nya~!!! 
I WANNA CHAOS! (>OwO)>u~!!(/OwO)/nya~!! (>OwO)>u~!(/OwO)/nya~! Let's\(OwO)/nya~ 
CHAOS CHAOS! (>OwO)>u~!!!(/OwO)/nya~!!! I WANNA CHAOS! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! (>OwO)>u~!(/OwO)/nya~! 
(>OwO)>u~!(/OwO)/nya~! Let's\(OwO)/nya~
```

## 範例輸出 #1

```
Hello World!
```
