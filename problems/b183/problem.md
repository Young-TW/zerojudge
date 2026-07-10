# b183. 4. 制服發放

## 內容

高雄世運要發放N件T-shirt分給M個義工，每人一件。在這裡N一定是 6 的倍數，且N>= M。T-shirt有6種 size，分別是：XXL，XL，L，M，S，XS。每種size T-shirt的數量都一樣。現在Victor有一個小問題，因為每個義工都只有2種T-shirt的size適合他。

你必須寫一個程式來決定是否可以發給每個義工一件適合他們的T-shirt。假如 N不等於M，那可以有一些T-shirt剩下。

## 輸入說明

第一列有2個正整數 N，M。N是6的倍數，1<=N<=36，代表T-shirt的數目。M，1<=M<=30，代表義工的數目，N>= M。接下來的M列，每列有2個size，分別代表各義工適合的size。

## 輸出說明

每組測試資料輸出一列，輸出能否發給每個義工一件適合他們的T-shirt。

## 範例輸入 #1

```
18 6
L XL
XL L
XXL XL
S XS
M S
M L
6 4
S XL
L S
L XL
L XL
```

## 範例輸出 #1

```
YES
NO
```
