#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const int MAXV = 500;
    int freq[MAXV + 1] = {0};

    long long n;
    while (cin >> n) {
        // read numbers and count frequencies
        for (long long i = 0; i < n; ++i) {
            int x;
            cin >> x;
            ++freq[x];
        }

        long long k = (n + 1) / 2;          // position of the median (1‑based)
        long long cum = 0;
        int answer = 0;
        for (int v = 1; v <= MAXV; ++v) {
            cum += freq[v];
            if (cum >= k) {
                answer = v;
                break;
            }
        }

        cout << answer << '\n';

        // reset frequencies for the next test case
        for (int v = 1; v <= MAXV; ++v) freq[v] = 0;
    }
    return 0;
}
