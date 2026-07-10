# j010. 11946 - Code Number

## 內容

Adrian 和 Maria 是住在不同城鎮的親戚。 由於他們居住在農村地區，他們很難保持聯繫。 他們發現克服溝通問題的一種方法是通過他們的父母的電話傳信。
關鍵是 Adrian 和 Maria 不想讓他們的父母閱讀他們的信息，他們決定為這些信息創建一個密碼。


代碼不是很複雜，但您應該記住，Adrian 和 Maria 只是孩子。
一般來說，消息的含義是基於用數字改變一些字母。


每條消息由幾行組成，使用英文字母的大寫字母、空格和標點符號：點和逗號。 由數字更改的字母可以在以下範例中看到


Message in “Code Number”:


H3LL0 MY L0V3, 1 M H499Y 83C4U53 500N 1 W1LL 83 70 Y0UR 51D3.
7H15 71M3 W17H0U7 Y0U H45 833N 373RN4L. 1 1NV173 Y0U 70 7H3 200
0N3 70 533 7H3 238R42 4ND 60R1L45.



Decode Message:


HELLO MY LOVE, I M HAPPY BECAUSE SOON I WILL BE TO YOUR SIDE.
THIS TIME WITHOUT YOU HAS BEEN ETERNAL. I INVITE YOU TO THE ZOO
ONE TO SEE THE ZEBRAS AND GORILAS.

## 輸入說明

第一行有一個數字 T (1 ≤ T ≤ 30)，代表測試資料數量


每份測試資料皆有一個空白行分隔


每份測試資料為一條用 Code Number 加密的訊息，1 ≤ 總共行數 ≤ 100


每行不會超過80個字符

## 輸出說明

對於每組測試資料，請輸出解碼的訊息


每個測試資料之間請空一行

## 範例輸入 #1

```
1
H3LL0 MY L0V3, 1 M H499Y 83C4U53 500N 1 W1LL 83 70 Y0UR 51D3. 7H15
71M3 W17H0U7 Y0U H45 833N 373RN4L. 1 1NV173 Y0U 70 7H3 200 0N3 70
533 7H3 238R45 4ND 60R1L45.
```

## 範例輸出 #1

```
HELLO MY LOVE, I M HAPPY BECAUSE SOON I WILL BE TO YOUR SIDE. THIS
TIME WITHOUT YOU HAS BEEN ETERNAL. I INVITE YOU TO THE ZOO ONE TO
SEE THE ZEBRAS AND GORILAS.
```
