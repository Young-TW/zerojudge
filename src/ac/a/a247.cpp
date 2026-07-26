#include <iostream>
using namespace std;

const int MAXN = 1000000;

int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int prim_count[MAXN + 1];
int min_z[MAXN + 1];
int add[MAXN + 2];
int used_count[MAXN + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 初始化 min_z 為極大值
    for (int i = 0; i <= MAXN; ++i) {
        min_z[i] = MAXN + 1;
    }

    // 生成所有 primitive triples
    for (int m = 2; m * m <= MAXN; ++m) {
        int m2 = m * m;
        for (int n = 1; n < m; ++n) {
            if (((m + n) & 1) && gcd(m, n) == 1) {
                int n2 = n * n;
                int c = m2 + n2;
                if (c > MAXN) continue;
                int a = m2 - n2;
                int b = 2 * m * n;
                prim_count[c]++;

                // 標記此 primitive triple 的所有倍數
                for (int k = 1; k * c <= MAXN; ++k) {
                    int ka = k * a;
                    int kb = k * b;
                    int kc = k * c;
                    if (min_z[ka] > kc) min_z[ka] = kc;
                    if (min_z[kb] > kc) min_z[kb] = kc;
                    if (min_z[kc] > kc) min_z[kc] = kc;
                }
            }
        }
    }

    // prim_count 前綴和：prim_count[N] = c <= N 的 primitive triples 數量
    for (int i = 1; i <= MAXN; ++i) {
        prim_count[i] += prim_count[i - 1];
    }

    // 利用 min_z 建立 used_count 的前綴和
    for (int i = 1; i <= MAXN; ++i) {
        if (min_z[i] <= MAXN) {
            add[min_z[i]]++;
        }
    }
    for (int i = 1; i <= MAXN; ++i) {
        used_count[i] = used_count[i - 1] + add[i];
    }

    int N;
    while (cin >> N) {
        if (N < 1) N = 1;
        if (N > MAXN) N = MAXN;
        cout << prim_count[N] << ' ' << N - used_count[N] << '\n';
    }

    return 0;
}
