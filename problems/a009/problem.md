# a009. 解碼器

## 內容

在密碼學裡面有一種很簡單的加密方式，就是把明碼的每個字元加上某一個整數K而得到密碼的字元（明碼及密碼字元一定都在ASCII碼中可列印的範圍內）。例如若K=2，那麼apple經過加密後就變成crrng了。解密則是反過來做。這個問題是給你一個密碼字串，請你依照上述的解密方式輸出明碼。


至於在本任務中K到底是多少，請自行參照Sample Input及Sample Output推出來吧！相當簡單的。

## 輸入說明

輸入共一行，每行含有1個字串，就是需要解密的明碼。

## 輸出說明

對每一測試資料，請輸出解密後的密碼。

## 範例輸入 #1

```
1JKJ'pz'{ol'{yhklthyr'vm'{ol'Jvu{yvs'Kh{h'Jvywvyh{pvu5

```

## 範例輸出 #1

```
*CDC is the trademark of the Control Data Corporation.
```

## 範例輸入 #2

```
1PIT'pz'h'{yhklthyr'vm'{ol'Pu{lyuh{pvuhs'I|zpulzz'Thjopul'Jvywvyh{pvu5
```

## 範例輸出 #2

```
*IBM is a trademark of the International Business Machine Corporation.

```
