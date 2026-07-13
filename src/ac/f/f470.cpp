#include <bits/stdc++.h>
using namespace std;

const uint32_t BASE = 1000000000;          // 1e9
const int MAX_IDX = 100000;                // exclusive upper bound
const int MAX_LEAD = 40;                   // needed leading digits

// big integer stored little‑endian, each limb < BASE
using BigInt = vector<uint32_t>;

BigInt addBig(const BigInt& a, const BigInt& b) {
    size_t n = max(a.size(), b.size());
    BigInt res;
    res.reserve(n + 1);
    uint64_t carry = 0;
    for (size_t i = 0; i < n; ++i) {
        uint64_t av = (i < a.size()) ? a[i] : 0;
        uint64_t bv = (i < b.size()) ? b[i] : 0;
        uint64_t sum = av + bv + carry;
        res.push_back(static_cast<uint32_t>(sum % BASE));
        carry = sum / BASE;
    }
    if (carry) res.push_back(static_cast<uint32_t>(carry));
    return res;
}

// return first up to maxDigits decimal digits of a (no leading zeros)
string leadingDigits(const BigInt& a, int maxDigits) {
    string s = to_string(a.back());               // most significant block
    for (int i = static_cast<int>(a.size()) - 2;
         i >= 0 && static_cast<int>(s.size()) < maxDigits; --i) {
        string blk = to_string(a[i]);
        s.append(9 - blk.length(), '0');
        s += blk;
    }
    if (static_cast<int>(s.size()) > maxDigits) s.resize(maxDigits);
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    vector<string> query(T);
    unordered_map<string, vector<int>> mp;
    mp.reserve(T * 2);
    for (int i = 0; i < T; ++i) {
        cin >> query[i];
        mp[query[i]].push_back(i);
    }
    vector<int> ans(T, -1);
    int remaining = T;

    // F(0) = 1, F(1) = 1
    BigInt f0(1, 1), f1(1, 1);
    auto process = [&](int idx, const BigInt& num) {
        string lead = leadingDigits(num, MAX_LEAD);
        int L = static_cast<int>(lead.size());
        for (int k = 1; k <= L; ++k) {
            string pref = lead.substr(0, k);
            auto it = mp.find(pref);
            if (it != mp.end()) {
                for (int qid : it->second) {
                    if (ans[qid] == -1) {
                        ans[qid] = idx;
                        --remaining;
                    }
                }
                mp.erase(it);
                if (remaining == 0) return true;
            }
        }
        return false;
    };

    // n = 0
    if (process(0, f0) && remaining == 0) {
        // all answered
    } else {
        // n = 1
        if (process(1, f1) && remaining == 0) {
            // done
        } else {
            BigInt prev = f0, cur = f1;
            for (int n = 2; n < MAX_IDX && remaining > 0; ++n) {
                BigInt nxt = addBig(prev, cur);
                if (process(n, nxt)) break;
                prev.swap(cur);
                cur.swap(nxt);
            }
        }
    }

    for (int i = 0; i < T; ++i) {
        cout << "Case #" << i + 1 << ": " << ans[i] << "\n";
    }
    return 0;
}
