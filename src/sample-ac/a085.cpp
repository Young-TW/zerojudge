#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int main() {
    string s, t;
    while (cin >> s >> t) {
        int start = 0, target = 0;
        for (int i = 0; i < 6; i++) start = start * 10 + (s[i] - '0');
        for (int i = 0; i < 6; i++) target = target * 10 + (t[i] - '0');

        // state = digits*6 + cursor; digits 0..999999, cursor 0..5
        // total 6,000,000 states
        vector<int> dist(6000000, -1);
        queue<int> q;
        int startState = start * 6 + 0; // cursor at position 0
        dist[startState] = 0;
        q.push(startState);

        // target check for any cursor
        bool found = false;
        int ans = -1;

        while (!q.empty() && !found) {
            int cur = q.front(); q.pop();
            int digits = cur / 6;
            int pos = cur % 6;
            int d = dist[cur];

            // decode digits into array
            int a[6];
            {
                int x = digits;
                for (int i = 5; i >= 0; i--) { a[i] = x % 10; x /= 10; }
            }

            if (digits == target) {
                ans = d;
                found = true;
                break;
            }

            int nd = d + 1;

            // 6 operations
            // Swap0: swap a[pos] with a[0]
            {
                if (pos != 0) {
                    int b[6]; memcpy(b, a, sizeof(a));
                    swap(b[pos], b[0]);
                    int ndig = 0; for (int i = 0; i < 6; i++) ndig = ndig * 10 + b[i];
                    int ns = ndig * 6 + pos;
                    if (dist[ns] == -1) { dist[ns] = nd; q.push(ns); }
                } else {
                    // no change
                }
            }
            // Swap1: swap a[pos] with a[5]
            {
                if (pos != 5) {
                    int b[6]; memcpy(b, a, sizeof(a));
                    swap(b[pos], b[5]);
                    int ndig = 0; for (int i = 0; i < 6; i++) ndig = ndig * 10 + b[i];
                    int ns = ndig * 6 + pos;
                    if (dist[ns] == -1) { dist[ns] = nd; q.push(ns); }
                }
            }
            // Up: a[pos]++ unless 9
            {
                if (a[pos] != 9) {
                    int b[6]; memcpy(b, a, sizeof(a));
                    b[pos]++;
                    int ndig = 0; for (int i = 0; i < 6; i++) ndig = ndig * 10 + b[i];
                    int ns = ndig * 6 + pos;
                    if (dist[ns] == -1) { dist[ns] = nd; q.push(ns); }
                }
            }
            // Down: a[pos]-- unless 0
            {
                if (a[pos] != 0) {
                    int b[6]; memcpy(b, a, sizeof(a));
                    b[pos]--;
                    int ndig = 0; for (int i = 0; i < 6; i++) ndig = ndig * 10 + b[i];
                    int ns = ndig * 6 + pos;
                    if (dist[ns] == -1) { dist[ns] = nd; q.push(ns); }
                }
            }
            // Left
            {
                if (pos != 0) {
                    int ns = digits * 6 + (pos - 1);
                    if (dist[ns] == -1) { dist[ns] = nd; q.push(ns); }
                }
            }
            // Right
            {
                if (pos != 5) {
                    int ns = digits * 6 + (pos + 1);
                    if (dist[ns] == -1) { dist[ns] = nd; q.push(ns); }
                }
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
