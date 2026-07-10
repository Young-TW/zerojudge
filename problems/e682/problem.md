# e682. 00531 - Compromise

## 內容

幾個月後，歐洲貨幣聯盟(the European Currency Union)將成為現實。
但是，要加入此聯盟，必須滿足Maastricht標準，這對於這些國家(也許是盧森堡除外)可能是困難的任務。
為了強制德國達到標準，政府有很多很棒的選擇(提高稅收，出售股票，對黃金儲備進行重估...)，以至於很難選擇該如何做。
因此，德國政府需要一項用於以下任務的計劃：
兩個政客各自輸入他們的建議。然後，電腦輸出在兩個建議中出現的最長共同單詞子序列。
如您所見，這是一個完全公平的折衷(畢竟，一個共同的單詞序列可以符合兩人的想法)。
您的國家/地區需要此程式，因此您的工作是為我們編寫程式。

## 輸入說明

輸入包含多組測資，每組測資包含兩句話。
每句話的單詞均為小寫，單詞由空格隔開，沒有標點符號。
所有單詞長度少於30個字元。每句話少於100個單詞，且至少有一個共同詞。
每句話以一個"#"的行結尾。

## 輸出說明

對於每組測資，輸出兩句話中的最長共同單詞子序列。

## 範例輸入 #1

```
die einkommen der landwirte
sind fuer die abgeordneten ein buch mit sieben siegeln
um dem abzuhelfen
muessen dringend alle subventionsgesetze verbessert werden
#
die steuern auf vermoegen und einkommen
sollten nach meinung der abgeordneten
nachdruecklich erhoben werden
dazu muessen die kontrollbefugnisse der finanzbehoerden
dringend verbessert werden
#
```

## 範例輸出 #1

```
die einkommen der abgeordneten muessen dringend verbessert werden
```
