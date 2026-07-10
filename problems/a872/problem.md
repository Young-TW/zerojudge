# a872. 12. Abbreviation Expansion

## 內容

伯特對於他建立的部落格網站Jitter有個新點子，希望能讓使用者對於常見的字能夠以縮寫取代，以便編輯新的部落格文章。當文章發布時，網頁會自動根據站內辭典將縮寫的本文擴增為普通文章，伯特認為如果使用者能夠省下這些輸入的時間將會促使這個網站更廣為人們所用。
 
請寫一支程式將縮寫的本文根據字典還原為一篇文章

## 輸入說明

輸入包含兩部分，第一部分是字典，單字間以空白隔開，第一部分和第二部分以"|"隔開，第二部分為縮寫的本文，單字間以空白隔開，以EOF結尾

## 輸出說明

輸出須將本文所有內容還原成一篇文章，一個縮寫的單字對其增加0個至數個字母後如果能在字典中找到相符合的單字則找到原文的匹配，但增加字母的數量需最少，如果同時找到兩個以上(含)的匹配時則輸出縮寫的本文

## 範例輸入 #1

```
cream chocolate every ever does do ice is fried friend friends lick
like floor favor flavor flower best but probably poorly say says that
what white our you your strawberry storyboard the | wht flvr ic crm ds
yr bst fnd lke? ur frds lk stbry, bt choc s prly th bs flr vr!
```

## 範例輸出 #1

```
what flavor ice cream does
your best friend like? our friends lk strawberry, but chocolate is poorly the best floor ever!
```
