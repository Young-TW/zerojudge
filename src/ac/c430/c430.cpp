#include <cstdio>
#include <string>
#include <cctype>
using namespace std;

int main() {
    // Read whitespace-separated tokens (single or multiple test cases, robust to EOF).
    // For a value N (1 <= N <= 10^40): min guesses = 0 if N==1, else 1.
    string tok;
    int c;
    while ((c = getchar()) != EOF) {
        if (isspace(c)) continue;
        // read one token
        tok.clear();
        do {
            if (!isspace(c)) tok.push_back((char)c);
            c = getchar();
        } while (c != EOF && !isspace(c));
        // strip leading zeros, ignore any stray non-digit (e.g. '\r')
        // keep only digits
        string digits;
        for (char ch : tok) if (ch >= '0' && ch <= '9') digits.push_back(ch);
        // remove leading zeros
        size_t p = digits.find_first_not_of('0');
        if (p == string::npos) digits = "0";
        else digits.erase(0, p);
        int ans = (digits == "1") ? 0 : 1;
        printf("%d\n", ans);
    }
    return 0;
}
