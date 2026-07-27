#include <bits/stdc++.h>
using namespace std;

/* ensure that vector v has at least sz elements, filling with 0 */
static void ensure_size(vector<int> &v, size_t sz) {
    if (v.size() < sz) v.resize(sz, 0);
}

/* build the whole sequence (start_digit = 5 or 6) up to max_len */
static void build_sequence(int start_digit, int max_len,
                           vector<string> &seq) {
    vector<int> a;          // number, least significant digit first
    vector<int> prod;       // a * a, same order

    a.push_back(start_digit);
    int sq = start_digit * start_digit;
    prod.push_back(sq % 10);
    prod.push_back(sq / 10);

    // length 1
    seq[1] = string(1, char('0' + start_digit));

    for (int len = 1; len < max_len; ++len) {   // current length = len
        /* ---- obtain t : k‑th digit of (prod - a) ---- */
        int k = len;                // position we need
        int borrow = 0, t = 0;
        for (int i = 0; i <= k; ++i) {
            int p = (i < (int)prod.size()) ? prod[i] : 0;
            int ai = (i < (int)a.size()) ? a[i] : 0;
            int cur = p - ai - borrow;
            if (cur < 0) { cur += 10; borrow = 1; }
            else          borrow = 0;
            if (i == k) t = cur;
        }

        /* ---- compute new digit d ---- */
        int d;
        if (start_digit == 5) {
            d = (10 - (t * 9) % 10) % 10;
        } else { // start_digit == 6
            d = (10 - t) % 10;
        }

        /* ---- update product using old a ---- */
        vector<int> old_a = a;          // copy of previous digits
        ensure_size(prod, 2 * (len + 1));

        // add 2*d*old_a shifted by len
        for (int i = 0; i < len; ++i) {
            long long add = 2LL * d * old_a[i];
            int pos = i + len;
            long long sum = prod[pos] + add;
            prod[pos] = int(sum % 10);
            long long carry = sum / 10;
            int j = pos + 1;
            while (carry > 0) {
                long long s2 = prod[j] + carry;
                prod[j] = int(s2 % 10);
                carry = s2 / 10;
                ++j;
            }
        }

        // add d*d at position 2*len
        long long sum = prod[2 * len] + 1LL * d * d;
        prod[2 * len] = int(sum % 10);
        long long carry = sum / 10;
        int j = 2 * len + 1;
        while (carry > 0) {
            long long s2 = prod[j] + carry;
            prod[j] = int(s2 % 10);
            carry = s2 / 10;
            ++j;
        }

        /* ---- append new digit ---- */
        a.push_back(d);

        /* ---- store string of length len+1 ---- */
        string s;
        s.reserve(len + 1);
        for (int i = len; i >= 0; --i) s.push_back(char('0' + a[i]));
        seq[len + 1] = s;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> queries;
    int n, maxN = 0;
    while (cin >> n) {
        queries.push_back(n);
        if (n > maxN) maxN = n;
    }
    if (maxN == 0) return 0;

    vector<string> seq5(maxN + 1), seq6(maxN + 1);
    build_sequence(5, maxN, seq5);
    build_sequence(6, maxN, seq6);

    for (int q : queries) {
        const string &s5 = seq5[q];
        const string &s6 = seq6[q];
        if (s5 < s6) {
            cout << s5 << '\n' << s6 << '\n';
        } else {
            cout << s6 << '\n' << s5 << '\n';
        }
    }
    return 0;
}
