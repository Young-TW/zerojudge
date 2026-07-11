#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int k, q, nq;
    while (cin >> k >> q >> nq) {
        if (k == q) {
            cout << "Illegal state" << endl;
            continue;
        }
        bool legal = false;
        if (nq != q && nq != k) {
            int qr = q / 8, qc = q % 8;
            int nr = nq / 8, nc = nq % 8;
            int kr = k / 8, kc = k % 8;
            if (qr == nr) {
                legal = true;
                if (kr == qr) {
                    int lo = min(qc, nc), hi = max(qc, nc);
                    if (kc > lo && kc < hi) legal = false;
                }
            } else if (qc == nc) {
                legal = true;
                if (kc == qc) {
                    int lo = min(qr, nr), hi = max(qr, nr);
                    if (kr > lo && kr < hi) legal = false;
                }
            }
        }
        if (!legal) {
            cout << "Illegal move" << endl;
            continue;
        }
        int kr = k / 8, kc = k % 8;
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        bool notAllowed = false;
        for (int d = 0; d < 4; d++) {
            int nr2 = kr + dr[d], nc2 = kc + dc[d];
            if (nr2 >= 0 && nr2 < 8 && nc2 >= 0 && nc2 < 8) {
                if (nr2 * 8 + nc2 == nq) {
                    notAllowed = true;
                    break;
                }
            }
        }
        if (notAllowed) {
            cout << "Move not allowed" << endl;
            continue;
        }
        bool canContinue = false;
        for (int d = 0; d < 4; d++) {
            int nr2 = kr + dr[d], nc2 = kc + dc[d];
            if (nr2 < 0 || nr2 >= 8 || nc2 < 0 || nc2 >= 8) continue;
            int kpos = nr2 * 8 + nc2;
            if (kpos == nq) continue;
            int qr2 = nq / 8, qc2 = nq % 8;
            int kpr = kpos / 8, kpc = kpos % 8;
            bool reachable = false;
            if (qr2 == kpr) {
                reachable = true;
                if (kr == qr2) {
                    int lo = min(qc2, kpc), hi = max(qc2, kpc);
                    if (kc > lo && kc < hi) reachable = false;
                }
            } else if (qc2 == kpc) {
                reachable = true;
                if (kc == qc2) {
                    int lo = min(qr2, kpr), hi = max(qr2, kpr);
                    if (kr > lo && kr < hi) reachable = false;
                }
            }
            if (!reachable) {
                canContinue = true;
                break;
            }
        }
        cout << (canContinue ? "Continue" : "Stop") << endl;
    }
    return 0;
}
