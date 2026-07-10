# a761. pA. 罐頭的記憶體

## 內容

罐頭，人稱頭頭，是一位熱衷於收藏記憶體的成功人，某天，他在吃便當的時候，發現白飯下面有一條記憶體(可能是煮飯阿姨不小心掉的)上面沾滿了飯粒與湯汁，由於頭頭是熱愛記憶體的人，在把記憶體清理乾淨後，要測試看看這條記憶體運作正常。

## 輸入說明

第一行有一個正整數 N, 代表頭頭對記憶體下了N條命令，命令有三種

1. map region a b ( a <= b )

2. load c

3. store d

其中 region , a , b , c , d 均為正整數，且 <= 2147483647
(詳細測資範圍在本題尾部提示)

第一條命令map為向記憶體取得區間 a ~ b 的使用權, 並給這段區間一個編號 region(記憶體區段的編號不會重複出現)
第二條命令load為讀取記憶體位置c
第三條命令store為儲存資料到記憶體位置d

## 輸出說明

* 對於map指令:

如果欲取得使用權的記憶體區段沒有被使用(即沒有與先前map過的記憶體區段有任何重疊)，

請輸出 "region R created"  (R 為該段記憶體編號)

否則請輸出 "fail to create region R, overlap with region O" (O為區間與R重疊到記憶體區段編號,如果同時與兩個區段記憶體區段重疊到，請輸出編號較小的)

* 對於load指令:

如果欲讀取的記憶體位置p有被map過了，請輸出"load from region R"(R為包含位置p的記憶體區段編號)

否則請輸出 "fail to load from p"

*對於store指令:

如果欲讀取的記憶體位置p有被map過了，請輸出"store to region R"(R為包含位置p的記憶體區段編號)

// 題目敘述已修正。by liouzhou_101 2015/7/6

否則請輸出 "fail to store to p"

## 範例輸入 #1

```
7
load 29       (尚未取得位置29使用權，因此讀取失敗)
map 1 25 39   (區段1  25-39 沒有與已創造任何記憶體區段重疊，因此創建成功)
map 2 23 24   (區段2  23-24 沒有與已創造任何記憶體區段重疊，因此創建成功)
map 3 22 25   (區段3  22-25 與區段1 與 區段2 重疊，創建失敗，輸出編號較小的區段1)
map 4 25 40   (區段4  25-40 與區段1重疊，創建失敗，輸出重疊的區段編號1)
store 33      (位置33在區段1之前，因此輸出區段編號1)
store 22      (尚未取得位置22使用權，因此讀取失敗)
```

## 範例輸出 #1

```
fail to load from 29
region 1 created
region 2 created
fail to create region 3, overlap with region 1
fail to create region 4, overlap with region 1
store region to 1
fail to store to 22
```
