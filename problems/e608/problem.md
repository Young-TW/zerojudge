# e608. 00630 - Anagrams (II)

## 內容

二十世紀末期人們最喜歡的遊戲之一是變位字謎。幾乎每家報紙和雜誌都有專門介紹變位字謎的專欄。
對於變位字謎還有專用的雜誌。舉辦了很多比賽，甚至還有了世界錦標賽。
現在有一個富豪也想跟上流行，他僱用你來幫助他，他希望你使用電腦來玩變位字謎，這樣他就能很快填完。
因此您需要寫一個程式，該程式使用給定的詞彙表來搜索給定單詞的變位字謎。

## 輸入說明

第一行包含一個整數T，代表測資數量。
每組測資第一行為一個空白行。
接下來每組測資具有以下結構：
<詞彙中的單詞數>
<單詞1>
.
.
.
<單詞N>
<測試詞1>
.
.
.
<測試詞k>
END
<詞彙中的單詞數>為一個整數N (N < 1000)。
<單詞1>到<單詞N>是詞彙表中的單詞。
 <測試詞1>到<測試詞k>是需要查找的變位字謎。
所有單詞均為小寫(最後一個單詞"END"表示測資結尾，不需用處理)。
所有單詞長度不超過20個字元。

## 輸出說明

對於每個<測試詞>(易位構詞)，按照順序輸出符合的單詞。
如果有符合的單詞，輸出格式如下：
"Anagrams for: <測試詞>"
"  1) <單詞>"
"  2) <單詞>"
.
.
以此類推...。
如果沒有符合的單詞，輸出格式如下：
"Anagrams for: <測試詞>"
"No anagrams for: <單詞>"


輸出測資間請用空白分隔。

## 範例輸入 #1

```
1

8
atol
lato
microphotographics
rata
rola
tara
tola
pies
tola
kola
aatr
photomicrographics
END
```

## 範例輸出 #1

```
Anagrams for: tola
  1) atol
  2) lato
  3) tola
Anagrams for: kola
No anagrams for: kola
Anagrams for: aatr
  1) rata
  2) tara
Anagrams for: photomicrographics
  1) microphotographics
```
