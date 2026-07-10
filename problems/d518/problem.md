# d518. 文字抄寫 II

## 內容

從機器中，不斷地出現 "?" 個英文字母的單字，現在要你抄寫下來，
 倘若這個單字已經出現過，則會使用編號上的號碼直接書寫
 倘若這個單字沒有出現過，則會賦予單字一個新的號碼

 每組新的測資，代表不同事件，請勿將其納入新的號碼

## 輸入說明

每組輸入的第一行 , 有一個數字 N ( 1 ≦ N ≦ 104 )

接下來會有瘋狂科學家講出的 N 行單字

每行由小寫字母 a 到 z 所構成的 ? 字單字. ( 1 ≦ ? ≦ 20 )

## 輸出說明

若這個字串之前已經出現過,則輸出號碼,若沒有則輸出它將被編寫的號碼.

## 範例輸入 #1

```
5
eine
isis
zwei
drei
zwei
6
abc
abcd
abdc
aabb
bca
abc
8
aaa
aab
aaa
aac
aaaabbbsc
caa
aaba
aab
```

## 範例輸出 #1

```
New! 1
New! 2
New! 3
New! 4
Old! 3
New! 1
New! 2
New! 3
New! 4
New! 5
Old! 1
New! 1
New! 2
Old! 1
New! 3
New! 4
New! 5
New! 6
Old! 2
```
