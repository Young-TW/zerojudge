#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

inline bool readInt(int &x) {
    x = 0;
    char c = getchar();
    if (c == EOF) return false;
    while (c != '-' && (c < '0' || c > '9')) {
        c = getchar();
        if (c == EOF) return false;
    }
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    if (neg) x = -x;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (readInt(N)) {
        if (!readInt(M)) break;
        vector<int> A(N), B(M);
        for (int i = 0; i < N; ++i) readInt(A[i]);
        for (int i = 0; i < M; ++i) readInt(B[i]);
        
        if (M == 0) {
            cout << 1 << "\n";
            continue;
        }
        if (N < M) {
            cout << "not found\n";
            continue;
        }

        vector<int> fail(M, 0);
        for (int i = 1, j = 0; i < M; ++i) {
            while (j > 0 && B[i] != B[j]) j = fail[j - 1];
            if (B[i] == B[j]) ++j;
            fail[i] = j;
        }

        int ans = -1;
        for (int i = 0, j = 0; i < N; ++i) {
            while (j > 0 && A[i] != B[j]) j = fail[j - 1];
            if (A[i] == B[j]) ++j;
            if (j == M) {
                ans = i - M + 2; // 1-indexed
                break;
            }
        }

        if (ans != -1) cout << ans << "\n";
        else cout << "not found\n";
    }
    return 0;
}
