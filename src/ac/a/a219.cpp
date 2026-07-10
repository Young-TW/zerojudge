#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int N;
int forbidden[16];
char perm[16];
char prevPerm[16];
bool hasPrev;
string outBuf;

void emit() {
    if (!hasPrev) {
        for (int i = 0; i < N; i++) outBuf += perm[i];
    } else {
        for (int i = 0; i < N; i++) {
            if (perm[i] != prevPerm[i]) outBuf += perm[i];
        }
    }
    outBuf += '\n';
    memcpy(prevPerm, perm, N);
    hasPrev = true;
}

void backtrack(int pos, int used) {
    if (pos == N) {
        emit();
        return;
    }
    for (int i = 0; i < N; i++) {
        if (used & (1 << i)) continue;
        if (forbidden[i] & (1 << (pos + 1))) continue;
        perm[pos] = 'A' + i;
        backtrack(pos + 1, used | (1 << i));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    bool firstCase = true;
    while (cin >> N) {
        for (int i = 0; i < N; i++) {
            forbidden[i] = 0;
            int x;
            while (cin >> x && x != 0) {
                if (x >= 1 && x <= 15) forbidden[i] |= (1 << x);
            }
        }
        hasPrev = false;
        outBuf.clear();
        backtrack(0, 0);
        if (!firstCase) cout << '\n';
        cout << outBuf;
        firstCase = false;
    }
    return 0;
}
