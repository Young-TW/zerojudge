# e854. 拼字問題

## 內容

有一位李先生從英文報紙上剪下 $\color{black}{n}$ 個大寫字母，希望可以拼貼出一封由大寫字母與空白字元組成的賀年字串 $\color{black}{L}$ 寄給朋友。請問這 $\color{black}{n}$ 個字母能從 $\color{black}{L}$ 的第一個字排到第幾個字，請將能拼出的部分顯示出來。例如，賀年卡 $\color{black}{L}$ 的內容為 HAPPY NEW YEAR，而 $n$ 個字母為 NAWPEHLP。則須顯示 HAPP。

## 輸入說明

第一行輸入字串 $\color{black}{L}$，$\color{black}{L}$ 由大寫字母與空白字元組成，$\color{black}{0 < |L| \le 100}$。
第二行輸入 $\color{black}{n}$ 個連續大寫字母，其中 $\color{black}{0 < n \le 100}$。

## 輸出說明

顯示所能拼出的文字（單字跟單字間要有一個空白字元）。假設至少可拼出一個字母。

## 範例輸入 #1

```
HAPPY NEW YEAR
AWPEHLPY
```

## 範例輸出 #1

```
HAPPY
```

## 範例輸入 #2

```
GOOD LUCK IN THE YEAR AHEAD
OMKLDLMONNG
```

## 範例輸出 #2

```
GOOD L
```
