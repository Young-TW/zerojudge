# n369. 3. 免費仔

## 內容

各大網路平台為了推銷自己的服務，會給予每支帳號一些免費試用功能，當試用期過了，就必須要付費使用，有的人為了不想付錢，會創建許多新的帳號來使用免費的功能，這些人被網友親切的稱之為「免費仔」。



![image](ShowImage?id=3934)

## 輸入說明

輸入的第一行有一個正整數 $N$（$1\le N\le 2000$），接下來下有 $N$ 行註冊操作，每行包含兩個以空白隔開的字串 $a, b$（$1\le |a|, |b|\le 1000$），$a$ 是註冊這個帳號時所使用的 Gmail，$b$ 是本次註冊用戶輸入的用戶名，輸入字串包含英文字母、數字與符號。

## 輸出說明

對於每一筆註冊操作，如果該 Gmail $a$ 尚未被使用，請輸出「welcome, 」加上用戶名 $b$；反之，請輸出用戶名 $b$ 加上「 account has been used」，見範例輸出。

## 範例輸入 #1

```
4
aBcD_1234@gmail.com HiHi
~~@gmail.com alex0301
~~@gmail.com HiHi
NotGmail M_SQRT
```

## 範例輸出 #1

```
welcome, HiHi
welcome, alex0301
HiHi account has been used
welcome, M_SQRT
```
