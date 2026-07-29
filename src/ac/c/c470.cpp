#include <bits/stdc++.h>
using namespace std;

static string BUF;
static size_t POS = 0;

// read next all-digit token (skip label/garbage tokens); returns false at EOF
static bool nextInt(long long &x) {
    while (POS < BUF.size()) {
        // skip whitespace
        while (POS < BUF.size() && isspace((unsigned char)BUF[POS])) POS++;
        if (POS >= BUF.size()) return false;
        size_t start = POS;
        while (POS < BUF.size() && !isspace((unsigned char)BUF[POS])) POS++;
        string tok = BUF.substr(start, POS - start);
        // validate: optional sign then all digits
        size_t s = 0;
        bool ok = !tok.empty();
        if (ok && (tok[0] == '-' || tok[0] == '+')) { s = 1; if (tok.size() == 1) ok = false; }
        for (size_t i = s; i < tok.size() && ok; i++) if (!isdigit((unsigned char)tok[i])) ok = false;
        if (ok) { x = stoll(tok); return true; }
        // else skip this token
    }
    return false;
}

int main() {
    // slurp stdin
    std::ostringstream ss;
    ss << std::cin.rdbuf();
    BUF = ss.str();

    string out;
    long long n;
    while (nextInt(n)) {
        long long sumOdd = 0, sumEven = 0; // 1-indexed parity
        for (long long i = 1; i <= n; i++) {
            long long a;
            if (!nextInt(a)) a = 0;
            if (i & 1) sumOdd += a; else sumEven += a;
        }
        out += to_string(max(sumOdd, sumEven));
        out += '\n';
    }
    std::cout << out;
    return 0;
}
