#include <bits/stdc++.h>
using namespace std;

int n0, n2, L;
int totalOdd, totalEven;
int need;                     // required remainder of odd_twos (mod 11)

// ------------------------------------------------------------
// feasibility test for a suffix
bool feasible(int zeros, int twos,
              int oddPos, int evenPos,
              int oddTwos) {
    if (zeros < 0 || twos < 0) return false;
    if (oddPos < 0 || evenPos < 0) return false;

    int low  = max(0, twos - evenPos);
    int high = min(oddPos, twos);
    if (low > high) return false;

    int cur = (need - oddTwos) % 11;
    if (cur < 0) cur += 11;
    int diff = (cur - (low % 11) + 11) % 11;
    int x = low + diff;               // smallest x ≥ low with correct remainder
    return x <= high;
}

// ------------------------------------------------------------
// build smallest (or largest) suffix, starting at position 'pos'
string build_suffix(int pos, int zeros, int twos,
                    int oddPos, int evenPos,
                    int oddTwos, bool smallest) {
    string res;
    for (int i = pos; i < L; ++i) {
        bool isOdd = (i % 2 == 0);          // position i (0‑based) is odd ⇔ i even
        if (smallest) {
            // try 0 first
            if (zeros > 0 &&
                feasible(zeros - 1, twos,
                         oddPos - (isOdd ? 1 : 0),
                         evenPos - (isOdd ? 0 : 1),
                         oddTwos)) {
                res.push_back('0');
                --zeros;
                if (isOdd) --oddPos; else --evenPos;
            } else {
                // must place 2
                res.push_back('2');
                --twos;
                if (isOdd) ++oddTwos;
                if (isOdd) --oddPos; else --evenPos;
            }
        } else {
            // try 2 first (largest)
            if (twos > 0 &&
                feasible(zeros, twos - 1,
                         oddPos - (isOdd ? 1 : 0),
                         evenPos - (isOdd ? 0 : 1),
                         oddTwos + (isOdd ? 1 : 0))) {
                res.push_back('2');
                --twos;
                if (isOdd) ++oddTwos;
                if (isOdd) --oddPos; else --evenPos;
            } else {
                // must place 0
                res.push_back('0');
                --zeros;
                if (isOdd) --oddPos; else --evenPos;
            }
        }
    }
    return res;
}

// ------------------------------------------------------------
// smallest valid string, empty if none
string smallest_string() {
    int zeros = n0, twos = n2;
    int oddPos = totalOdd, evenPos = totalEven;
    int oddTwos = 0;
    string ans;
    for (int i = 0; i < L; ++i) {
        bool isOdd = (i % 2 == 0);
        // try 0
        if (zeros > 0 &&
            feasible(zeros - 1, twos,
                     oddPos - (isOdd ? 1 : 0),
                     evenPos - (isOdd ? 0 : 1),
                     oddTwos)) {
            ans.push_back('0');
            --zeros;
            if (isOdd) --oddPos; else --evenPos;
        } else {
            // must be 2
            if (twos == 0) return "";
            if (!feasible(zeros, twos - 1,
                          oddPos - (isOdd ? 1 : 0),
                          evenPos - (isOdd ? 0 : 1),
                          oddTwos + (isOdd ? 1 : 0))) return "";
            ans.push_back('2');
            --twos;
            if (isOdd) ++oddTwos;
            if (isOdd) --oddPos; else --evenPos;
        }
    }
    return ans;
}

// ------------------------------------------------------------
// largest valid string, empty if none
string largest_string() {
    int zeros = n0, twos = n2;
    int oddPos = totalOdd, evenPos = totalEven;
    int oddTwos = 0;
    string ans;
    for (int i = 0; i < L; ++i) {
        bool isOdd = (i % 2 == 0);
        // try 2 first
        if (twos > 0 &&
            feasible(zeros, twos - 1,
                     oddPos - (isOdd ? 1 : 0),
                     evenPos - (isOdd ? 0 : 1),
                     oddTwos + (isOdd ? 1 : 0))) {
            ans.push_back('2');
            --twos;
            if (isOdd) ++oddTwos;
            if (isOdd) --oddPos; else --evenPos;
        } else {
            // must be 0
            if (zeros == 0) return "";
            if (!feasible(zeros - 1, twos,
                          oddPos - (isOdd ? 1 : 0),
                          evenPos - (isOdd ? 0 : 1),
                          oddTwos)) return "";
            ans.push_back('0');
            --zeros;
            if (isOdd) --oddPos; else --evenPos;
        }
    }
    return ans;
}

// ------------------------------------------------------------
// next valid string after 'cur' (lexicographically), empty if none
string next_valid(const string &cur) {
    // prefix data
    vector<int> prefZero(L + 1, 0), prefTwo(L + 1, 0), prefOddTwos(L + 1, 0);
    for (int i = 0; i < L; ++i) {
        prefZero[i + 1] = prefZero[i] + (cur[i] == '0');
        prefTwo[i + 1]  = prefTwo[i]  + (cur[i] == '2');
        prefOddTwos[i + 1] = prefOddTwos[i];
        if (cur[i] == '2' && (i % 2 == 0)) ++prefOddTwos[i + 1];
    }

    for (int i = L - 1; i >= 0; --i) {
        if (cur[i] != '0') continue;          // only 0 → 2 is an increase
        int zeros_used   = prefZero[i];
        int twos_used    = prefTwo[i];
        int oddTw_used   = prefOddTwos[i];

        int zeros_used_new = zeros_used;               // still a zero count
        int twos_used_new  = twos_used + 1;            // we place a 2 here
        int oddTw_new      = oddTw_used + ((i % 2 == 0) ? 1 : 0);

        int zeros_rem = n0 - zeros_used_new;
        int twos_rem  = n2 - twos_used_new;

        int odd_used_prefix = (i + 2) / 2;                 // odd positions up to i (inclusive)
        int even_used_prefix = (i + 1) - odd_used_prefix;

        int odd_rem  = totalOdd  - odd_used_prefix;
        int even_rem = totalEven - even_used_prefix;

        if (feasible(zeros_rem, twos_rem, odd_rem, even_rem, oddTw_new)) {
            string res = cur.substr(0, i);
            res.push_back('2');
            string suffix = build_suffix(i + 1,
                                          zeros_rem, twos_rem,
                                          odd_rem, even_rem,
                                          oddTw_new, true);
            res += suffix;
            return res;
        }
    }
    return "";
}

// ------------------------------------------------------------
// previous valid string before 'cur' (lexicographically), empty if none
string prev_valid(const string &cur) {
    // prefix data
    vector<int> prefZero(L + 1, 0), prefTwo(L + 1, 0), prefOddTwos(L + 1, 0);
    for (int i = 0; i < L; ++i) {
        prefZero[i + 1] = prefZero[i] + (cur[i] == '0');
        prefTwo[i + 1]  = prefTwo[i]  + (cur[i] == '2');
        prefOddTwos[i + 1] = prefOddTwos[i];
        if (cur[i] == '2' && (i % 2 == 0)) ++prefOddTwos[i + 1];
    }

    for (int i = L - 1; i >= 0; --i) {
        if (cur[i] != '2') continue;          // only 2 → 0 is a decrease
        int zeros_used   = prefZero[i];
        int twos_used    = prefTwo[i];
        int oddTw_used   = prefOddTwos[i];

        int zeros_used_new = zeros_used + 1;          // we place a 0 here
        int twos_used_new  = twos_used;               // we remove the 2
        int oddTw_new      = oddTw_used;              // no new odd‑two

        int zeros_rem = n0 - zeros_used_new;
        int twos_rem  = n2 - twos_used_new;

        int odd_used_prefix = (i + 2) / 2;                 // odd positions up to i (inclusive)
        int even_used_prefix = (i + 1) - odd_used_prefix;

        int odd_rem  = totalOdd  - odd_used_prefix;
        int even_rem = totalEven - even_used_prefix;

        if (feasible(zeros_rem, twos_rem, odd_rem, even_rem, oddTw_new)) {
            string res = cur.substr(0, i);
            res.push_back('0');
            string suffix = build_suffix(i + 1,
                                          zeros_rem, twos_rem,
                                          odd_rem, even_rem,
                                          oddTw_new, false);
            res += suffix;
            return res;
        }
    }
    return "";
}

// ------------------------------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n0 >> n2) {
        L = n0 + n2;
        totalOdd  = (L + 1) / 2;
        totalEven = L / 2;
        need = (int)((1LL * n2 * 6) % 11);   // 6 = inverse of 2 modulo 11

        string sMin = smallest_string();
        string sMax = largest_string();

        if (sMin.empty() || sMax.empty()) {
            cout << -1 << '\n';
            continue;
        }

        string secondMin = next_valid(sMin);
        string secondMax = prev_valid(sMax);

        if (secondMin.empty() || secondMax.empty()) {
            cout << -1 << '\n';
        } else {
            cout << secondMax << '\n';
            cout << secondMin << '\n';
        }
    }
    return 0;
}
