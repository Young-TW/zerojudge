# a221. 11734 - Big Number of Teams will Solve This

## 內容

為一個簡單的程式題目撰寫一個程式碼並不是太大的問題,


但是缺乏經驗的新人並不太知道,自己的輸出需要完全與 Judges的相同。


通常的時候,他們會輸出多餘的空格,因為他們認為這樣會讓輸出變的更好看。


 


但是真實的狀況是:你輸出的每一個字元都應該跟 Judges 的一模一樣


如果在提交 Judges的時候多輸出空格,你將會得到 "輸出格式錯誤" (Output Format Error)


如果在 Judges 忽略空格後,輸出仍不正確,則會得到 "錯誤答案" (Wrong Answer)


而 "正確" (Yes) 則會在輸出完全匹配的時候獲得。


 


在這一題,你需要判定提交者的輸出 ,並且給出 Judges 的判定。

## 輸入說明

在第一行會給出一個正整數 t (t<20) 代表 共有幾組資料


每組資料會有兩行


第一行為 隊伍的輸出


第二行是 Judges的輸出


每行至少會有一個字,最多20個字


 


隊伍的的輸出由空白跟字組成, Judges的輸出則只有字

## 輸出說明

對於每組資料


你需要輸出一行


每一行包含了裁決編號 跟 裁決結果


請看範例測試

## 範例輸入 #1

```
3
yes
yes
Casematters
casematters
no space        please
nospaceplease
```

## 範例輸出 #1

```
Case 1: Yes
Case 2: Wrong Answer
Case 3: Output Format Error
```
