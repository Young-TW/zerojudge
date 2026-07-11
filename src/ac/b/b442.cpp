#pragma GCC optimize("O3")
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
	Matrix multiply(const Matrix& x) const {
		Matrix ret(row, x.col);
		for (int i = 0; i < row; i++) {
			int* ret_row = ret.data[i].data();
			const int* a_row = data[i].data();
			for (int k = 0; k < col; k++) {
				int r = a_row[k];
				const int* b_row = x.data[k].data();
				for (int j = 0; j < x.col; j++) {
					ret_row[j] += r * b_row[j];
				}
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
		return (x * 2654435761LU) & 0xFFFFFFFFLU;
	}
};

int main() {
	int N, S1, S2;
	while (scanf("%d %d %d", &N, &S1, &S2) == 3) {
		Matrix A(N, N), B(N, N), C;
		A.rand_gen(S1);
		B.rand_gen(S2);
		C = A.multiply(B);		
		printf("%lu\n", C.signature());
	}
	return 0;
}
