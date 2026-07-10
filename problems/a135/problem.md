# a135. 12250 - Language Detection

## 內容

![image](ShowImage?id=22)
英文、西班牙文、德文、法文、義大利文及俄文為歐盟國家中最盛行的 6 種語言。左圖顯示英語人口在歐洲各國的密度。這些語言都有不同的字來表示英文的「HELLO」。例如西班牙文中等同於英文「HELLO」的字是「HOLA」，而德文、法文、義大利文及俄文中意思為(或相近)「HELLO」的字依序為「HALLO」、「BONJOUR」、「CIAO」和「ZDRAVSTVUJTE」。

你在本題中的任務非常簡單。給你以上的幾個單字之一或是其他的單字，你需要辨識它是哪一種語言。

## 輸入說明

輸入檔含有大約 2000 行的輸入。每行含有一個字串 S。你可以假設所有的字母都是大寫英文字母，且字串的最大長度為 14。輸入以僅含有一個「#」的一行作為結束，該行不需處理。

## 輸出說明

除了最後一行以外，相對於每一行輸入都要有一行輸出。
這行輸出含有輸出的序號及語言名稱。如果輸入的字串是「HELLO」、「HOLA」、「HALLO」、「BONJOUR」、「CIAO」或「ZDRAVSTVUJTE」時，你要回報它是哪一種語言。如果輸入字串是這 6 個以外的字串則印出字串「UNKNOWN」。所有的輸出字串也都是大寫。詳細的格式細節請參見範例輸出。

## 範例輸入 #1

```
HELLO
HOLA
HALLO
BONJOUR
CIAO
ZDRAVSTVUJTE
#
```

## 範例輸出 #1

```
Case 1: ENGLISH
Case 2: SPANISH
Case 3: GERMAN
Case 4: FRENCH
Case 5: ITALIAN
Case 6: RUSSIAN
```
