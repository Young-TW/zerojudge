# b444. 期望試驗 快速冪次

## 內容

背景曾經某 M 被期望值坑，就只是在計算 $x^y \mod z$ 時偷偷替換成 $x^{y-1} \times x \mod z$，結果得到 Time Limit Exceeded。

 根據分析 $y = 16$ 時，用二進制表示為 $(10000)_{2}$，若變成 $y = 15$，就會變成 $(01111)_{2}$，通常快速求冪的乘法次數與二進制的 1 個數成正比，所以速度就慢非常多。 

```
typedef unsigned long long UINT64;
UINT64 mul(UINT64 a, UINT64 b, UINT64 mod) { 
	UINT64 ret = 0; 
	for (a = a >= mod ? a%mod : a, b = b >= mod ? b%mod : b; b != 0; b>>=1, a = mod ? a - mod : a) { 
		if (b&1) {
			ret += a;
			if (ret >= mod) 
				ret -= mod;
		} 
	} 
	return ret; 
}
UINT64 mpow(UINT64 x, UINT64 y, UINT64 mod) {
	UINT64 ret = 1;
	while (y) {
		if (y&1)
			ret = mul(ret, x, mod);
		y >>= 1, x = mul(x, x, mod);
	}
	return ret;
} 
```
  問題描述讓我們來一場 $x^y \mod z$ 的期望值試驗吧，基礎目標是減少乘法次數。

其中 $1 \le x, z \le 10^{18}$, $0 \le y \le 2^{2^{20}}$，在這場試驗中展現你的優化吧。

## 輸入說明

多組測資，每一組測資一行三個整數 $x, y, z$。

- $1 \le x, z \le 10^{18}$
- $0 \le y \le 2^{2^{20}}$，由一個二進制字串 $S$ 表示，為了方便起見 $S$ 的長度為 $2^k$

## 輸出說明

對於每組測資輸出一行， $x^y \mod z$ 的數值。

## 範例輸入 #1

```
5 01 7
5 10 7
5 0101 7
3 0110 7
```

## 範例輸出 #1

```
5
4
3
1
```
