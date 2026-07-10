# b055. 6. 吸血鬼數（Vampire Number）

## 內容

Vampire Number是一種特別的數字，定義為若合成數 v(註一)有偶數個位n，且是n/2個位的正整數x和y的積，而且x和y不是同時以0為個位數，組成x和y的數字，剛好就是v的數字，那麼v就是吸血鬼數（vampire number），而x和y則稱為尖牙。


他由兩個稱為fang的數字相乘得到，這兩個fangs的位數同是Vampire Number的一半位數，且Vampire Number將由fang的各個位數的數字排列組合而成(例如：30[fang]x51[fang]=1530[vampire number])，但是fangs不均為10的倍數。


求出4位數、6位數、8位數的Vampire Numbers中偶數的Vampire Number。


[Vampire Number的例子]


(fang)x(fang)=(Vampire Number)


21x60=1260(4位數)


30x51=1530(4位數)


246x510=125460(6位數)


615x204=125460(6位數)

## 輸入說明

輸入一個數字 n，表示輸出所有n位數的Vampire Numbers

## 輸出說明

輸出n位數的Vampire Numbers，由小到大輸出並且不可重複。

## 範例輸入 #1

```
4(表示輸出4位數的結果)
```

## 範例輸出 #1

```
1260
1530
6880
```
