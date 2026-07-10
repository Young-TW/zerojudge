# b442. 快取實驗 矩陣乘法

## 內容

背景
記得 b439: 快取置換機制 提到的快取置換機制嗎？現在來一場實驗吧！

題目描述相信不少人都已經實作所謂的矩陣乘法，計算兩個方陣大小為 $N \times N$ 的矩陣 $A, B$。為了方便起見，提供一個偽隨機數的生成，減少在輸入處理浪費的時間，同時也減少上傳測資的辛苦。

根據種子 $c = S1$ 生成矩陣 $A$，種子 $c = S2$ 生成矩陣 $B$，計算矩陣相乘 $A \times B$，為了方便起見，使用 hash 函數進行簽章，最後輸出一個值。由於會牽涉到 overflow 問題，此題作為快取實驗就不考慮這個，overflow 問題大家都會相同。 

請利用快取優勢修改代碼如下：

#include <bits/stdc++.h>
using namespace std;
class Matrix {
public:
	vector< vector<int> > data;
	int row, col;
	Matrix(int n = 1, int m = 1) {
		data = vector< vector<int> >(n, vector<int>(m, 0));
		row = n, col = m;
	}
	void rand_gen(int c) {
		int x = 2, n = row * col;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				x = ((long long) x * x + c + i + j)%n;
				data[i][j] = x;
			}
		}
	}
	Matrix multiply(Matrix x) {
		Matrix ret(row, x.col);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < x.col; j++) {
				int sum = 0;	// overflow
				for (int k = 0; k < col; k++)
					sum += data[i][k] * x.data[k][j];
				ret.data[i][j] = sum;
			}
		}
		return ret;
	}
	void print() {
		for (int i = 0; i < row; i++) {
			printf("[");
			for (int j = 0; j < col; j++) {
				printf(" %d", data[i][j]);
			}
			printf(" ]\n");
		}
	}
	unsigned long signature() {
		unsigned long h = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				h = hash(h + data[i][j]);
			}
		}
		return h;
	}
private:
	unsigned long hash(unsigned long x) {
		return (x * 2654435761LU);
	}
};
int main() {
	int N, S1, S2;
	while (scanf("%d %d %d", &N, &S1, &S2) == 3) {
		Matrix A(N, N), B(N, N), C;
		A.rand_gen(S1);
		B.rand_gen(S2);
		C = A.multiply(B);		
//		A.print();
//		B.print();
//		C.print();
		printf("%lu\n", C.signature());
	}
	return 0;
}

## 輸入說明

多組測資，每組測資一行三個整數 $N, S1, S2$。

- $1 \le N \le 1000$
- $0 \le S1, S2 \le 65536$

## 輸出說明

每組測資輸出一行，一個整數 signature 的結果。

## 範例輸入 #1

```
2 2 5
2 2 5
```

## 範例輸出 #1

```
573770929
573770929
```
