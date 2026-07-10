# f463. Cellphone Typing

## 內容

12526 Cellphone Typing  原題連結
A research team is developing a new technology to save time when typing text messages in mobile devices. 
They are working on a new model that has a complete keyboard, so users can type any single letter by pressing the corresponding key. 
In this way, a user needs P keystrokes to type a word of length P.
However, this is not fast enough. The team is going to put together a dictionary of the common words that a user may type. 
The goal is to reduce the average number of keystrokes needed to type words that are in the dictionary. 
During the typing of a word, whenever the following letter is uniquely determined, 
the cellphone system will input it automatically, without the need for a keystroke.
一個研究小組正在開發一項新技術，以節省在移動設備中鍵入文本消息時的時間。
他們正在使用具有完整鍵盤的新型號，因此用戶可以通過按相應的鍵來鍵入任何單個字母。
這樣，用戶需要進行P次擊鍵才能鍵入長度為P的單詞。
但是，這還不夠快。 該團隊將把用戶可以鍵入的常用單詞的詞典放在一起。
目的是減少鍵入字典中單詞所需的平均擊鍵次數。
在輸入單詞期間，只要唯一確定以下字母，
手機系統無需按鍵即可自動輸入。
To be more precise, the behavior of the cellphone system will be determined by the following rules:
 1. The system never guesses the rst letter of a word, so the rst letter always has to be input manually by pressing the corresponding key.
 2. If a non-empty succession of letters c1c2...cn has been input, and there is a letter c such that every word in the dictionary which starts with 
 c1c2...cn also starts with c1c2...cnc, 
 then the system inputs c automatically, without the need of a keystroke. Otherwise, the system waits for the user.
更準確地說，手機系統的行為將由以下規則決定：
 1.系統永遠不會猜測單詞的第一個字母，因此始終必須通過按相應的鍵來手動輸入第一個字母。
 2.如果輸入了一個非空連續的字母c1c2...cn，並且有一個字母c，則字典中以c1c2...cn開頭的每個單詞也都以c1c2...cnc開頭，
 則系統無需按鍵即可自動輸入c。 否則，系統將等待用戶。
For instance, if the dictionary is composed of the words `hello', `hell', `heaven' and `goodbye', and the user presses `h', 
the system will input `e' automatically, because every word which starts with `h' also starts with `he'. 
However, since there are words that start with `hel' and with `hea', the system now needs to wait for the user. 
If the user then presses `l', obtaining the partial word `hel', the system will input a second `l' automatically. 
When it has `hell' as input, the system cannot guess, because it is possible that the word is over, or it is also possible that the user may want to press `o' to get `hello'. 
例如，如果字典由單詞“ hello”，“ hell”，“ heaven”和“goodbye”組成，並且用戶按下“ h”，
系統會自動輸入“ e”，因為每個以“ h”開頭的單詞也都以“ he”開頭。
但是，由於存在以“ hel”和“ hea”開頭的單詞，因此系統現在需要等待用戶。
如果用戶隨後按下“ l”以獲得部分單詞“ hel”，則係統將自動輸入第二個“ l”。
當輸入“ hell”時，系統將無法猜測，因為該單詞可能已經結束，或者用戶也可能想按“ o”來獲取“ hello”。
In this fashion, to type the word `hello' the user needs three keystrokes, `hell' requires two, and `heaven' also requires two, because when the current input 
is `hea' the system can automatically input the remainder of the word by repeatedly applying the second rule. 
Similarly, the word `goodbye' needs just one keystroke, because after pressing the initial `g' the system will automatically ll in the entire word. 
In this example, the average number of keystrokes needed to type a word in the dictionary is then (3 + 2 + 2 + 1)/4 = 2.00.
Your task is, given a dictionary, to calculate the average number of keystrokes needed to type a word in the dictionary with the new cellphone system.
以這種方式，鍵入單詞“ hello”時，用戶需要擊鍵三次，“ hell”需要擊鍵兩次，“ heaven”也需要擊鍵兩次，因為噹噹前輸入時
如果為“ hea”，則係統可以通過重複應用第二條規則來自動輸入單詞的其餘部分。
同樣，“再見”一詞只需要敲擊一次，因為按了首字母“ g”後，系統會自動將整個單詞填滿。
在此示例中，在字典中鍵入單詞所需的平均擊鍵次數為（3 + 2 + 2 + 1）/ 4 = 2.00。
給定詞典，您的任務是計算使用新手機系統在詞典中鍵入單詞所需的平均擊鍵次數。

## 輸入說明

Each test case is described using several lines. The rst line contains an integer N representing the
number of words in the dictionary (1<=N<=10^5). Each of the next N lines contains a non-empty
string of at most 80 lowercase letters from the English alphabet, representing a word in the dictionary.
Within each test case all words are dierent, and the sum of the lengths of all words is at most 10^6.
每個測試用例用幾行描述。 第一行包含一個整數N，代表
字典中的單詞數（1<=N<=10^5）。 接下來的N行中的每行都包含一個非空
英文字母中最多80個小寫字母的字符串，代表字典中的一個單詞。
在每個測試用例中，所有單詞都是不同的，並且所有單詞的長度之和最多為10^6。

## 輸出說明

For each test case output a line with a rational number representing the average number of keystrokes
needed to type a word in the dictionary. The result must be output as a rational number with exactly
two digits after the decimal point, rounded if necessary.
對於每個測試用例，輸出一行帶有合理數字的行，該行代表擊鍵的平均次數
需要在字典中輸入一個單詞。 結果必須作為有理數精確地輸出
小數點後兩位數字，如有必要四捨五入。

## 範例輸入 #1

```
4
hello
hell
heaven
goodbye
3
hi
he
h
7
structure
structures
ride
riders
stress
solstice
ridiculous
```

## 範例輸出 #1

```
2.00 
1.67
2.71
```

## 範例輸入 #2

```
8
a
b
c
d
e
f
g
ah

8
b
c
d
g
ab
ac
ad
abc
```

## 範例輸出 #2

```
1.13
1.63
```
