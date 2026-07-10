# c106. 00271 - Simply Syntax

## 內容

在 Hedonia 島上的官方語言是 Hedonian 語。有位 Hedonian 語言學教授發現她的許多學生並未弄明白 Hedonian 語的語法規則。她實在是厭煩了訂正學生的語法錯誤，所以她決定要她的學生們寫個程式，能夠檢查出他們寫的句子中的語法錯誤。就跟 Hedonian 人的天性一樣，Hedonian 語的文法規則也相當單純，規則如下：



0.
這個語言中僅有 p 到 z，還有 N，C，D，E，I 這幾個字母。
1.
從 p 到 z 中，任何一個字母都是一個正確的句子。
2.
如果 s 是一個正確的句子，那麼 Ns 也是。
3.
如果 s 及 t 都是正確的句子，那麼 Cst, Dst, Est 還有 Ist 也都是正確的句子。
4.
0. 到 3. 是檢查一個句子是否合乎語法僅有的規則。

你被要求寫程式檢查一個句子是否滿足上述的規則 0. 到 4.。

## 輸入說明

輸入中含有許多句子，每個句子一列，都只含有 p 到 z 還有 N, C, D, E, I這幾個字母。你可以假設每個句子至多有 256 個字母，至少 1 個字母。

## 輸出說明

對於一個格式正確的句子輸出 YES，對於一個錯誤的句子則輸出 NO。

## 範例輸入 #1

```
Cp
Isz
NIsz
Cqpq
IzIst
IIszz
IIszIsz
IIszIIIszzIsz
NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNCst
zN
zzI
st
z
```

## 範例輸出 #1

```
NO
YES
YES
NO
YES
YES
YES
YES
YES
NO
NO
NO
YES
```
