# d313. FROM GENE TO PROTEIN

## 內容

小寢是一位才華洋溢的科學家，然而雖然他的才華出眾，卻有一點深深地困擾著他--那就是他的長相十分醜陋。照鏡子時，鏡子會破裂、出門時，小孩看到會被嚇哭、照相時，相機甚至無法對焦在他的臉上。小寢知道這是基因的問題，因此決定研究自己的基因。你的任務非常簡單，就是將小寢的基因密碼轉譯成胺基酸。

此表列出了64種密碼子以及胺基酸的標準配對。(取自維基) 第二位鹼基UCAG第
一
位
鹼
基UUUU (Phe/F)苯丙氨酸
UUC (Phe/F)苯丙氨酸
UUA (Leu/L)亮氨酸
UUG (Leu/L)亮氨酸

UCU (Ser/S)絲氨酸
UCC (Ser/S)絲氨酸
UCA (Ser/S)絲氨酸
UCG (Ser/S)絲氨酸

UAU (Tyr/Y)酪氨酸
UAC (Tyr/Y)酪氨酸
UAA 終止
UAG 終止

UGU (Cys/C)半胱氨酸
UGC (Cys/C)半胱氨酸
UGA 終止
UGG (Trp/W)色氨酸

CCUU (Leu/L)亮氨酸
CUC (Leu/L)亮氨酸
CUA (Leu/L)亮氨酸
CUG (Leu/L)亮氨酸

CCU (Pro/P)脯氨酸
CCC (Pro/P)脯氨酸
CCA (Pro/P)脯氨酸
CCG (Pro/P)脯氨酸

CAU (His/H)組氨酸
CAC (His/H)組氨酸
CAA (Gln/Q)谷氨醯胺
CAG (Gln/Q)谷氨醯胺

CGU (Arg/R)精氨酸
CGC (Arg/R)精氨酸
CGA (Arg/R)精氨酸
CGG (Arg/R)精氨酸

AAUU (Ile/I)異亮氨酸
AUC (Ile/I)異亮氨酸
AUA (Ile/I)異亮氨酸
AUG (Met/M)甲硫氨酸, 起始1

ACU (Thr/T)蘇氨酸
ACC (Thr/T)蘇氨酸
ACA (Thr/T)蘇氨酸
ACG (Thr/T)蘇氨酸

AAU (Asn/N)天冬醯胺
AAC (Asn/N)天冬醯胺
AAA (Lys/K)賴氨酸
AAG (Lys/K)賴氨酸

AGU (Ser/S)絲氨酸
AGC (Ser/S)絲氨酸
AGA (Arg/R)精氨酸
AGG (Arg/R)精氨酸

GGUU (Val/V)纈氨酸
GUC (Val/V)纈氨酸
GUA (Val/V)纈氨酸
GUG (Val/V)纈氨酸

GCU (Ala/A)丙氨酸
GCC (Ala/A)丙氨酸
GCA (Ala/A)丙氨酸
GCG (Ala/A)丙氨酸

GAU (Asp/D)天冬氨酸
GAC (Asp/D)天冬氨酸
GAA (Glu/E)谷氨酸
GAG (Glu/E)谷氨酸

GGU (Gly/G)甘氨酸
GGC (Gly/G)甘氨酸
GGA (Gly/G)甘氨酸
GGG (Gly/G)甘氨酸

1標準起始編碼，同時為甲硫氨酸編碼。mRNA中第一個AUG就是蛋白質翻譯的起始部位。

## 輸入說明

輸入為一段鹼基密碼(長度不超過200個字元)。

以'0'作為結束，不須對本行做任何輸出。

請參考輸入範例。

## 輸出說明

第一行輸出 Case " 密碼 ":

接下來輸出轉譯出的胺基酸，之間請以'-'作為分隔。

蛋白質可能不只一個，之間以換行作分隔

請參考輸出範例。

## 範例輸入 #1

```
5'-AUGUAA
5' -AAUGUGA
3' AAUGUAAUAGUGUAA
5'-UCAUGGGGAAACCCUUUUAAAUGCGUGCAUGA
0
```

## 範例輸出 #1

```
Case " 5'-AUGUAA ":
Met
Case " 5' -AAUGUGA ":
Met
Case " 3' AAUGUAAUAGUGUAA ":
Met
Met
Case " 5'-UCAUGGGGAAACCCUUUUAAAUGCGUGCAUGA ":
Met-Gly-Lys-Pro-Phe
Met-Arg-Ala
```
