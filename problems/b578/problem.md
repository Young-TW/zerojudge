# b578. 一個角

## 內容

故事是這樣的，某天...


某李瑋: 阿就腦袋鈍鈍的阿...
 某duck: 它有尖尖的過嗎
 某duck: 還是直角
 某李瑋: 有時候會突然變尖
 某李瑋: 今天有尖一次
 某duck: (Pusheen Sticker)
 某李瑋: 好啦 所以?
 某duck: 加油
 某李瑋: 給點提示
 某duck: (Tuzki Sticker)
 某李瑋: 甚麼拉
 某duck: Sqrt不夠嗎
 某李瑋: 等等在想一下怎麼用
 某李瑋: 除了sqrt還要甚麼嗎?
 某duck: 建質數表
 某李瑋: ㄝ對ㄝ
 某李瑋: 你還沒教我
 某duck: (Tuzki Sticker)



所以題目是這樣：



 給你一個三角形的邊長，請你判斷它是銳角 (acute)、直角 (right)、或是鈍角 (obtuse) 三角形。

## 輸入說明

第一行會有一個正整數 T ，表示測試資料的數量。
 對於每筆測試資料會有3個正整數 a b c ，表示三角型的三邊長

 1<= T <=10000，保證 a b c 可形成面積大於0的三角形
 90% 測試資料中 1<= a ,b ,c <= 46340
 10% 測試資料中 1<= a ,b ,c <= 2^32 (4294967296)

## 輸出說明

依三角形的類別輸出"acute triangle"、"right triangle"、或"obtuse triangle"。

## 範例輸入 #1

```
2
3 4 5
1 1 1
```

## 範例輸出 #1

```
right triangle
acute triangle
```
