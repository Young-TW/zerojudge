# e685. 00732 - Anagrams by Stack

## 內容

堆疊式操作如何產生變位字謎？
以下為使用stack操作，將TROT轉換為TORT的兩種方法：
[
i i i i o o o o
i o i i o o i o
]
其中"i"代表Push，"o"代表Pop。
現在給你兩個單詞，請您輸出將原始單詞轉換為目標單詞的stack操作所有方法。

## 輸入說明

輸入包含多組測資，每組測資兩行。
第一行為原始單詞。 
第二行為目標單詞。

## 輸出說明

對於每組測資，輸出將原始單詞轉換為目標單詞的stack操作所有方法。
方法請按字典順序排列。
每組測資請用以下符號區隔：
[
]
詳細格式請見範例輸出。

## 範例輸入 #1

```
madam
adamm
bahama
bahama
long
short
eric
rice
```

## 範例輸出 #1

```
[
i i i i o o o i o o
i i i i o o o o i o
i i o i o i o i o o
i i o i o i o o i o
]
[
i o i i i o o i i o o o
i o i i i o o o i o i o
i o i o i o i i i o o o
i o i o i o i o i o i o
]
[
]
[
i i o i o i o o
]
```
