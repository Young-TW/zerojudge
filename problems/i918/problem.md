# i918. 12626 - I ❤ Pizza

## 內容

每個人都喜歡各種披薩: Margarita, Four cheese, Salami, Caprichosa, Neapolitan, Hawaiian...


著名的比薩瑪格麗塔是以意大利薩沃伊女王瑪格麗塔命名的。據說主廚拉斐爾·埃斯波西托（Raffaele Esposito）讓她從他專門為女王準備的各種披薩中選擇。瑪格麗塔選擇這款披薩是為了紀念意大利國旗的顏色：紅番茄、白奶酪和綠色羅勒。
然而，有人爭辯說，事實上，瑪格麗塔王后不喜歡洋蔥，而且其他披薩都有洋蔥，她別無選擇，只能吃那個披薩。
在我們特殊的電腦化廚房中，食材以大寫字母命名：“A”、“B”、“C”、“D”、...
因此，要製作瑪格麗塔披薩，我們需要與字母一樣多的成分，即一個“M”、三個“A”、兩個“R”、一個“G”、一個“I”和一個“T”。
例如，如果我們有以下成分：


AAAAAAMMRRTITIGGRRRRRRRR


我們可以做 2 個 MARGARITA 披薩，還可以留出一些“R”。
給定一組配料，你必須說出可以製作多少個瑪格麗塔披薩。請注意，可能有剩餘成分，也可能有不必要的成分，例如“B”。

## 輸入說明

第一行有一個數字 N 代表測試資料數量


接下來 N 行，每行代表現有成分，成分只包含大寫英文字母A ~ Z


一行最多 600 個字母

## 輸出說明

對於每組測試資料


輸出可以製作多少 "MARGARITA" 披薩

## 範例輸入 #1

```
5
MARGARITA
AAAAAAMMRRTITIGGRRRRRRRR
AMARGITA
BOLOGNESACAPRICHOSATOMATERA
ABCDEFGHIJKLMNOPQRSTUVWXYZ
```

## 範例輸出 #1

```
1
2
0
1
0
```
