#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <cstdint>
#include <utility>

using namespace std;
using u64 = uint64_t;

const u64 BASE1 = 131;
const u64 BASE2 = 137;
const int MAXLEN = 100;

u64 powBase1[MAXLEN + 1];
u64 powBase2[MAXLEN + 1];

struct PairHash {
    size_t operator()(const pair<u64, u64>& p) const noexcept {
        return p.first ^ (p.second + 0x9e3779b97f4a7c15ULL + (p.first << 6) + (p.first >> 2));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    powBase1[0] = 1;
    powBase2[0] = 1;
    for (int i = 1; i <= MAXLEN; ++i) {
        powBase1[i] = powBase1[i - 1] * BASE1;
        powBase2[i] = powBase2[i - 1] * BASE2;
    }

    int m;
    while (cin >> m) {
        vector<string> arr(m);
        unordered_set<pair<u64, u64>, PairHash> hashSet;
        hashSet.reserve(m * 2);

        for (int i = 0; i < m; ++i) {
            cin >> arr[i];
            const string& s = arr[i];
            u64 h1 = 0, h2 = 0;
            for (char c : s) {
                h1 = h1 * BASE1 + (c - 'a' + 1);
                h2 = h2 * BASE2 + (c - 'a' + 1);
            }
            hashSet.insert({h1, h2});
        }

        long long ans = 0;
        for (const string& s : arr) {
            int n = s.size();
            if (n < 2) continue;

            u64 H1[MAXLEN + 1];
            u64 H2[MAXLEN + 1];
            H1[0] = 0;
            H2[0] = 0;
            for (int i = 0; i < n; ++i) {
                H1[i + 1] = H1[i] * BASE1 + (s[i] - 'a' + 1);
                H2[i + 1] = H2[i] * BASE2 + (s[i] - 'a' + 1);
            }

            for (int lenY = 1; lenY <= (n - 1) / 2; ++lenY) {
                u64 pre1 = H1[lenY];
                u64 suf1 = H1[n] - H1[n - lenY] * powBase1[lenY];
                if (pre1 != suf1) continue;

                u64 pre2 = H2[lenY];
                u64 suf2 = H2[n] - H2[n - lenY] * powBase2[lenY];
                if (pre2 != suf2) continue;

                int midLen = n - 2 * lenY;
                u64 mid1 = H1[n - lenY] - H1[lenY] * powBase1[midLen];
                u64 mid2 = H2[n - lenY] - H2[lenY] * powBase2[midLen];

                if (hashSet.find({mid1, mid2}) != hashSet.end()) {
                    ++ans;
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
