#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cctype>
using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string line;
    while (getline(cin, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n' || line.back() == ' ' || line.back() == '\t')) {
            line.pop_back();
        }
        bool allLetters = !line.empty();
        for (size_t i = 0; i < line.size(); i++) {
            unsigned char c = (unsigned char)line[i];
            if (!isalpha(c)) {
                allLetters = false;
                break;
            }
        }
        if (!allLetters) {
            cout << line << "\n";
            continue;
        }
        int cnt[26];
        memset(cnt, 0, sizeof(cnt));
        for (size_t i = 0; i < line.size(); i++) {
            unsigned char c = (unsigned char)line[i];
            if (c >= 'a' && c <= 'z') cnt[c - 'a']++;
            else if (c >= 'A' && c <= 'Z') cnt[c - 'A']++;
        }
        int maxn = 0, minn = 1000000;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] > 0) {
                if (cnt[i] > maxn) maxn = cnt[i];
                if (cnt[i] < minn) minn = cnt[i];
            }
        }
        int diff = maxn - minn;
        if (isPrime(diff)) {
            cout << "Lucky Word\n" << diff << "\n";
        } else {
            cout << "No Answer\n" << 0 << "\n";
        }
    }
    return 0;
}
