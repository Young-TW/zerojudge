#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<int> a(N);
        for (int i = 0; i < N; ++i) cin >> a[i];

        // doctor becomes free at this minute (first idle minute)
        int free_min = 0;
        bool left = false;
        int answer = -1;

        for (int i = 0; i < N; ++i) {
            int arrive = a[i];
            if (arrive >= free_min) {                 // idle before patient
                int idle = arrive - free_min;         // number of idle minutes
                if (idle >= 30) {                     // doctor leaves now
                    answer = free_min + 30;
                    left = true;
                    break;
                }
                // patient is examined starting at its arrival minute
                free_min = arrive + 5;
            } else {                                   // patient waits
                free_min += 5;                         // examined immediately
            }
        }

        if (!left) {
            // after the last patient
            answer = free_min + 30;
        }

        cout << answer << '\n';
    }
    return 0;
}
