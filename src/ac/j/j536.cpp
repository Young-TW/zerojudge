#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    long long A;
    while (cin >> N >> A) {
        vector<long long> v(N);
        long long total = 0;
        for (int i = 0; i < N; ++i) {
            cin >> v[i];
            total += v[i];
        }
        int c = 0;
        for (int i = 1; i < N; ++i)
            if (v[i] > v[c]) c = i;
        long long half = A / 2;
        long long L = c, R = N - 1 - c;
        long long takeL = min(L, half);
        long long need = half - takeL;
        long long takeR = min(R, half + need);
        long long need2 = (half + need) - takeR;
        takeL = min(L, takeL + need2);
        long long absorbed = 0;
        for (long long i = c - takeL; i <= c + takeR; ++i)
            absorbed += v[i];
        cout << absorbed << ' ' << total - absorbed << '\n';
    }
    return 0;
}
