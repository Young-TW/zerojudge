# k202. 13055 - Inception

## 內容

Dom Cobb 和他的搭檔 Arthur 通過進入目標的潛意識來執行非法行為。他們使用夢中夢的兩級夢策略來提取有價值的信息。 入夢者可能被突然的（"Kick"）驚醒，或者可能在夢中死去。


現在 Dom 需要你的幫助。因為他有一項複雜的任務。他必須經歷很多人的夢境。 他從一個人的夢境旅行到另一個人的夢境。但是他太累了，以至於他無法再知道自己是醒著還是在別人的夢裡。


現在有 n 個詢問去處理，每個詢問會是以下幾種形式之一：
"Sleep X"——這意味著名為 X 的人將要睡覺，而 Dom 將進入 X 的夢境，從前個人的夢境進去（如果有的話）。
"Kick"——這意味著 Dom 進入其夢中的當前人將被喚醒，Dom 將從他進入此夢境的地方返回到前一個人的夢境中。如果 Dom 不再存在於任何人的夢境中，請忽略此查詢。
"Test"——這意味著 Dom 想知道他現在在誰的夢境裡。 您必須輸出此人的姓名。 如果此時 Dom 不在任何人的夢中，你必須輸出"Not in a dream"

## 輸入說明

第一行包含一個整數 n (1 ≤ n ≤ 10000)，即查詢次數。


以下 n 行中的每一行都將包含上述三個查詢之一。


對於"Sleep X"查詢，X 將是一個僅由大寫或小寫字母組成且長度不超過 15 個字元的字串。

## 輸出說明

對於每個“Test”查詢，輸出 Dom 所在的夢境的人的名子，與輸入中出現的完全一樣。 如果 Dom 不在任何人的夢境中，則輸出“Not in a dream”。

## 範例輸入 #1

```
20
Sleep Dom
Sleep Sakin
Test
Sleep Asif
Sleep Mushfiq
Test
Kick
Test
Sleep Shafi
Test
Kick
Test
Kick
Test
Kick
Test
Kick
Test
Kick
Test
```

## 範例輸出 #1

```
Sakin
Mushfiq
Asif
Shafi
Asif
Sakin
Dom
Not in a dream
Not in a dream
```
