#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long A, D;
    while (cin >> A >> D) {
        int N;
        if (!(cin >> N)) break;
        vector<long long> diff;
        diff.reserve(N);
        for (int i = 0; i < N; ++i) {
            long long UA, UD;
            cin >> UA >> UD;
            diff.push_back(UA - UD);
        }
        long long target = D - A;
        if (target == 0) {
            cout << 1 << '\n';
            continue;
        }
        int n1 = N / 2;
        int n2 = N - n1;
        vector<long long> left(diff.begin(), diff.begin() + n1);
        vector<long long> right(diff.begin() + n1, diff.end());

        vector<long long> sumsL;
        sumsL.reserve(1ULL << n1);
        for (unsigned int mask = 0; mask < (1U << n1); ++mask) {
            long long s = 0;
            for (int i = 0; i < n1; ++i)
                if (mask & (1U << i)) s += left[i];
            sumsL.push_back(s);
        }

        vector<long long> sumsR;
        sumsR.reserve(1ULL << n2);
        for (unsigned int mask = 0; mask < (1U << n2); ++mask) {
            long long s = 0;
            for (int i = 0; i < n2; ++i)
                if (mask & (1U << i)) s += right[i];
            sumsR.push_back(s);
        }
        sort(sumsR.begin(), sumsR.end());

        bool ok = false;
        for (long long sL : sumsL) {
            long long need = target - sL;
            if (binary_search(sumsR.begin(), sumsR.end(), need)) {
                ok = true;
                break;
            }
        }
        cout << (ok ? 1 : 0) << '\n';
    }
    return 0;
}
