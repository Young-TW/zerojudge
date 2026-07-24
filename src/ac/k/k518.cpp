#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

const unsigned long long BASE1 = 131ULL;
const unsigned long long BASE2 = 137ULL;
const unsigned long long MOD1 = 1000000007ULL;
const unsigned long long MOD2 = 1000000009ULL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string S;
    while (cin >> S) {
        int n;
        if (!(cin >> n)) break;

        unordered_map<int, unordered_set<unsigned long long>> dict1, dict2;
        vector<int> lengths;
        vector<bool> len_exists(1001, false);

        for (int i = 0; i < n; ++i) {
            string word;
            cin >> word;
            int len = word.length();
            if (len > 0 && len <= 1000) {
                if (!len_exists[len]) {
                    len_exists[len] = true;
                    lengths.push_back(len);
                }
                unsigned long long h1 = 0, h2 = 0;
                for (char c : word) {
                    h1 = (h1 * BASE1 + c) % MOD1;
                    h2 = (h2 * BASE2 + c) % MOD2;
                }
                dict1[len].insert(h1);
                dict2[len].insert(h2);
            }
        }

        sort(lengths.begin(), lengths.end());
        lengths.erase(unique(lengths.begin(), lengths.end()), lengths.end());

        int L = S.length();
        vector<unsigned long long> pow1(L + 1), pow2(L + 1);
        vector<unsigned long long> hash1(L + 1), hash2(L + 1);

        pow1[0] = pow2[0] = 1;
        for (int i = 0; i < L; ++i) {
            pow1[i + 1] = (pow1[i] * BASE1) % MOD1;
            pow2[i + 1] = (pow2[i] * BASE2) % MOD2;
            hash1[i + 1] = (hash1[i] * BASE1 + S[i]) % MOD1;
            hash2[i + 1] = (hash2[i] * BASE2 + S[i]) % MOD2;
        }

        vector<bool> dp(L + 1, false);
        dp[0] = true;

        for (int i = 0; i < L; ++i) {
            if (!dp[i]) continue;
            for (int len : lengths) {
                if (i + len > L) break;
                unsigned long long h1 = (hash1[i + len] - hash1[i] * pow1[len] % MOD1 + MOD1) % MOD1;
                unsigned long long h2 = (hash2[i + len] - hash2[i] * pow2[len] % MOD2 + MOD2) % MOD2;
                if (dict1[len].count(h1) && dict2[len].count(h2)) {
                    dp[i + len] = true;
                }
            }
        }

        cout << (dp[L] ? "yes" : "no") << "\n";
    }

    return 0;
}
