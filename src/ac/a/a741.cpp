#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

static void build(long long n, string &s) {
    if (n >= 10000000LL) {
        build(n / 10000000LL, s);
        s += " kuti";
        n %= 10000000LL;
    }
    if (n >= 100000LL) {
        s += " " + to_string(n / 100000LL) + " lakh";
        n %= 100000LL;
    }
    if (n >= 1000LL) {
        s += " " + to_string(n / 1000LL) + " hajar";
        n %= 1000LL;
    }
    if (n >= 100LL) {
        s += " " + to_string(n / 100LL) + " shata";
        n %= 100LL;
    }
    if (n > 0) {
        s += " " + to_string(n);
    }
}

int main() {
    long long n;
    int caseno = 1;
    while (cin >> n) {
        string s;
        build(n, s);
        if (s.empty()) s = " 0";
        printf("%4d.%s\n", caseno++, s.c_str());
    }
    return 0;
}
