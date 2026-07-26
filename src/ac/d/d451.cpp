#include <bits/stdc++.h>
using namespace std;

// remove commas from a string
static string stripCommas(const string &src) {
    string dst;
    dst.reserve(src.size());
    for (char c : src) if (c != ',') dst.push_back(c);
    return dst;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        for (int tc = 0; tc < N; ++tc) {
            string raw;
            int p;
            cin >> raw >> p;
            string s = stripCommas(raw);

            // locate decimal point
            size_t dotPos = s.find('.');

            // collect all digits, remember first non‑zero digit
            vector<int> allDigits;
            size_t firstPos = string::npos;          // position in s
            size_t startIdx = 0;                     // index in allDigits
            for (size_t i = 0; i < s.size(); ++i) {
                if (s[i] == '.') continue;
                int d = s[i] - '0';
                if (firstPos == string::npos && d != 0) {
                    firstPos = i;
                    startIdx = allDigits.size();     // index of this digit
                }
                allDigits.push_back(d);
            }

            // ----- zero case -------------------------------------------------
            if (firstPos == string::npos) {
                cout << '0';
                if (p > 1) {
                    cout << '.';
                    for (int i = 0; i < p - 1; ++i) cout << '0';
                }
                cout << "x10(0)\n";
                continue;
            }

            // ----- exponent --------------------------------------------------
            long long exponent = 0;
            if (dotPos == string::npos) {
                exponent = static_cast<long long>(s.size() - 1 - firstPos);
            } else if (firstPos < dotPos) {
                exponent = static_cast<long long>(dotPos - 1 - firstPos);
            } else {
                exponent = -static_cast<long long>(firstPos - dotPos);
            }

            // ----- prepare digits for rounding -------------------------------
            vector<int> sig;
            for (size_t i = startIdx; i < allDigits.size(); ++i)
                sig.push_back(allDigits[i]);

            // pad with zeros so we have at least p+1 digits
            while (sig.size() < static_cast<size_t>(p + 1))
                sig.push_back(0);

            // ----- rounding ---------------------------------------------------
            int carry = (sig[p] >= 5) ? 1 : 0;
            for (int i = p - 1; i >= 0; --i) {
                int sum = sig[i] + carry;
                sig[i] = sum % 10;
                carry = sum / 10;
            }
            if (carry) {
                sig.insert(sig.begin(), 1);
                ++exponent;
            }

            // keep exactly p digits (the possible extra leading digit is already
            // accounted for by the exponent increase)
            if (static_cast<int>(sig.size()) > p)
                sig.resize(p);

            // ----- output -----------------------------------------------------
            cout << sig[0];
            if (p > 1) {
                cout << '.';
                for (int i = 1; i < p; ++i) cout << sig[i];
            }
            cout << "x10(" << exponent << ")\n";
        }
    }
    return 0;
}
