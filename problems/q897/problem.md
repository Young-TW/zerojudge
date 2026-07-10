# q897. 156 - Ananagrams

## 內容

Most crossword puzzle fans are used to anagrams — groups of words with the same letters in different orders — for example OPTS, SPOT, STOP, POTS and POST. Some words however do not have this attribute, no matter how you rearrange their letters, you cannot form another word. Such words are called ananagrams, an example is QUIZ. Obviously such definitions depend on the domain within which we are working; you might think that ATHENE is an ananagram, whereas any chemist would quickly produce ETHANE. One possible domain would be the entire English language, but this could lead to some problems. One could restrict the domain to, say, Music, in which case SCALE becomes a relative ananagram (LACES is not in the same domain) but NOTE is not since it can produce TONE. Write a program that will read in the dictionary of a restricted domain and determine the relative ananagrams. Note that single letter words are, ipso facto, relative ananagrams since they cannot be “rearranged” at all. The dictionary will contain no more than 1000 words.


大多數玩填字遊戲的人對「anagram（變位詞）」應該不陌生，例如這些字：OPTS, SPOT, STOP, POTS and POST。它們都由相同的字母組成，只是順序不同。不過，也有些字是「無法透過任何字母重新排列」而構成其他字的，例如：QUIZ 這種無法變形為其他單字的字叫做 ananagram（非重組詞）。


給定一個有限詞庫中所有單字，請你找出這些單字中哪些字是「relative ananagrams」（相對非重組詞）——也就是在這個詞庫中，沒有其他單字是它的變位詞。

## 輸入說明

Input will consist of a series of lines. No line will be more than 80 characters long, but may contain any number of words. Words consist of up to 20 upper and/or lower case letters, and will not be broken across lines. Spaces may appear freely around words, and at least one space separates multiple words on the same line. Note that words that contain the same letters but of differing case are considered to be anagrams of each other, thus ‘tIeD’ and ‘EdiT’ are anagrams. The file will be terminated by a line consisting of a single ‘#’.

多行文字，每行至多 80 個字元
每行包含數個單字，單字長度最多 20 個英文字母（大小寫皆有可能出現）
單字之間由數個空白隔開，行首行尾可以有空白
字母大小寫不重要（也就是 Stop 與 Pots 是變位詞）
最後一行僅包含 # 代表輸入結束

## 輸出說明

Output will consist of a series of lines. Each line will consist of a single word that is a relative ananagram in the input dictionary. Words must be output in lexicographic (case-sensitive) order. There will always be at least one relative ananagram.

按照字典順序將所有「relative ananagrams」列出

## 範例輸入 #1

```
ladder came tape soon leader acme RIDE lone Dreis peat
ScAlE orb eye Rides dealer NotE derail LaCeS drIed
noel dire Disk mace Rob dries
#
```

## 範例輸出 #1

```
Disk
NotE
derail
drIed
eye
ladder
soon
```
