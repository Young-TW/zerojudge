#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

long long factorial[11];

void precompute_factorial() {
    factorial[0] = 1;
    for (int i = 1; i <= 10; ++i) factorial[i] = factorial[i-1] * i;
}

long long count_permutations(const vector<int>& count, int total_digits) {
    long long res = factorial[total_digits];
    for (int i = 0; i <= 9; ++i) {
        res /= factorial[count[i]];
    }
    return res;
}

long long count_leading_zero(const vector<int>& count, int total_digits) {
    if (count[0] == 0) return 0;
    vector<int> new_count = count;
    new_count[0]--;
    return count_permutations(new_count, total_digits - 1);
}

int main() {
    precompute_factorial();
    int n, K;
    while (cin >> n >> K) {
        long long ans = 0;
        set<vector<int>> seen;
        
        int half_len = (n + 1) / 2;
        int start = 1;
        for (int i = 1; i < half_len; ++i) start *= 10;
        int end = start * 10 - 1;
        
        for (int num = start; num <= end; ++num) {
            string s = to_string(num);
            string full = s;
            if (n % 2 == 1) {
                for (int i = (int)s.size() - 2; i >= 0; --i) {
                    full += s[i];
                }
            } else {
                for (int i = (int)s.size() - 1; i >= 0; --i) {
                    full += s[i];
                }
            }
            
            long long pal_val = stoll(full);
            if (pal_val % K != 0) continue;
            
            vector<int> cnt(10, 0);
            for (char c : full) {
                cnt[c - '0']++;
            }
            
            if (seen.count(cnt)) continue;
            seen.insert(cnt);
            
            long long total = count_permutations(cnt, n);
            long long lz = count_leading_zero(cnt, n);
            ans += (total - lz);
        }
        
        cout << ans << endl;
    }
    return 0;
}
