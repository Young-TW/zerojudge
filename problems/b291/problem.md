# b291. 生態調查

## 內容

~故事劇情請自行腦補~

總之你現在有個任務，你會陸續看到一些動物在一些地方，請你統計某地方有幾隻某動物。

## 輸入說明

第一行有一個數字N(0<N<=1000)
接下來N行格式為
動物名稱 數量 地點
(動物名稱與地點皆只包含小寫英文，且長度不超過20，數量為不大於100的正整數)

## 輸出說明

請輸出
地點 : 動物名 數量, 動物名 數量
請照地點名稱出現順序輸出
請照動物名稱出現順序輸出
一個地點一行

## 範例輸入 #1

```
6
monkey 2 tree
snail 1 ground
jackyliuxx 2 ground
snail 1 tree
monkey 1 ground
snail 3 ground
```

## 範例輸出 #1

```
tree : monkey 2, snail 1
ground : monkey 1, snail 4, jackyliuxx 2
```
