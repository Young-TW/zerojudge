#include <bits/stdc++.h>
using namespace std;

inline bool isPartial(int a, int b) {
    // (a & b) != 0 && (a & ~b) != 0 && (b & ~a) != 0
    return (a & b) && (a & ~b) && (b & ~a);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    string Xs;
    cin >> Xs;
    vector<int> S(n);
    for (int i = 0; i < n; ++i) {
        string t; cin >> t;
        int mask = 0;
        for (char c : t) mask |= 1 << (c - 'a');
        S[i] = mask;
    }

    int Xmask = 0;
    for (char c : Xs) Xmask |= 1 << (c - 'a');

    long long P1 = 0, P2 = 0, P3 = 0, P4 = 0;

    for (int mask : S) {
        if ((Xmask & mask) == 0) {
            ++P1;                     // disjoint
        } else if ((Xmask & ~mask) == 0 && Xmask != mask) {
            ++P2;                     // Si properly contains X
        } else if ((mask & ~Xmask) == 0 && mask != Xmask) {
            ++P3;                     // X properly contains Si
        } else {
            ++P4;                     // partial intersection
        }
    }

    long long P5 = 0;
    // enumerate all non‑empty proper sub‑masks of Xmask
    for (int sub = Xmask; sub; sub = (sub - 1) & Xmask) {
        if (sub == Xmask) continue;          // whole set, not allowed
        int other = Xmask ^ sub;             // X2, automatically non‑empty
        bool ok = true;
        for (int mask : S) {
            if (isPartial(sub, mask) || isPartial(other, mask)) {
                ok = false;
                break;
            }
        }
        if (ok) ++P5;
    }

    cout << P1 << ' ' << P2 << ' ' << P3 << ' ' << P4 << ' ' << P5 << '\n';
    return 0;
}
