# d710. parking lot

## 內容

國防大學的停車場上，

 停了許多各式各樣的車子，

 有 Ford 的小轎車，

 有 Toyota 的柴電混合車，

 還有 BMW 的休旅車，

 此外，

 有藍色的車、紅色的車、白色的車 ... 

 

 看完以上敘述，

 你知道今天要寫什麼程式了嗎？

 給一些車子的顏色和廠牌，

 再依照指示列出有哪些車子符合要求。

## 輸入說明

每組測試資料分三部分。

 第一部分有兩個數字 n, m ，( 0 < n, m ≤ 20 )

 代表有 n 輛車子，

 m 個指示。

 第二部分有 n 行，

 每行包含兩個字串：廠牌、顏色。( 以空白隔開，廠牌全部大寫，顏色全部小寫 ) 

 第三部份有 m 行，

 每行包含兩個字串，

 分為兩種情況：brand XXXX 或 color xxxxx 。( 廠牌全部大寫，顏色全部小寫 )

 每組測試資料間有一空行。

## 輸出說明

brand XXXXX 的意思是列出 XXXXX 廠牌 的車子，

 color xxxxx 的意思是列出 xxxxx 顏色 的車子。

 每行格式為 "廠牌 顏色"

 保證一定有資料輸出。 

 列出順序以讀入先後為主。

 每組測試資料間請留一空行。

## 範例輸入 #1

```
5 2
NISSAN red
BMW white
ROLLSROYCE black
TOYOTA white
TOYOTA blue
brand TOYOTA
color white

3 1
LEXUS pink
FORD green
PORSCHE gray
color pink
```

## 範例輸出 #1

```
TOYOTA white
TOYOTA blue
BMW white
TOYOTA white

LEXUS pink
```
