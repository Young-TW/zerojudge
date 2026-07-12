#include <cstdio>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

const int BUFFER_SIZE = 1 << 20;
char buf[BUFFER_SIZE];
int p = 0, len = 0;

inline char getChar() {
    if (p == len) {
        len = fread(buf, 1, BUFFER_SIZE, stdin);
        p = 0;
        if (len == 0) return EOF;
    }
    return buf[p++];
}

inline bool readInt(int &x) {
    char c = getChar();
    while (c != EOF && (c < '0' || c > '9')) {
        c = getChar();
    }
    if (c == EOF) return false;
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getChar();
    }
    return true;
}

int main() {
    int n;
    if (!readInt(n)) return 0;
    
    vector<array<long long, 3>> dice;
    dice.reserve(n);
    
    for (int i = 0; i < n; ++i) {
        int a, b, c, d, e, f;
        readInt(a); readInt(b); readInt(c); readInt(d); readInt(e); readInt(f);
        
        int mn1 = a < d ? a : d;
        int mx1 = a < d ? d : a;
        int mn2 = b < e ? b : e;
        int mx2 = b < e ? e : b;
        int mn3 = c < f ? c : f;
        int mx3 = c < f ? f : c;
        
        long long v1 = ((long long)mn1 << 32) | (unsigned int)mx1;
        long long v2 = ((long long)mn2 << 32) | (unsigned int)mx2;
        long long v3 = ((long long)mn3 << 32) | (unsigned int)mx3;
        
        array<long long, 3> arr = {v1, v2, v3};
        sort(arr.begin(), arr.end());
        dice.push_back(arr);
    }
    
    sort(dice.begin(), dice.end());
    int unique_count = static_cast<int>(unique(dice.begin(), dice.end()) - dice.begin());
    
    printf("%d\n", unique_count);
    
    return 0;
}
