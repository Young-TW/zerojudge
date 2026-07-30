#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        long long cnt[6] = {};
        for (int i = 0; i < N; i++) {
            int x;
            cin >> x;
            if (0 <= x && x <= 5) cnt[x]++;
        }

        long long smoothie = cnt[0];
        long long cakes = cnt[1] + cnt[2] + cnt[3] + cnt[4] + cnt[5];
        long long combo = min(smoothie, cakes);
        long long total = combo * 59 + (smoothie - combo) * 50 + (cakes - combo) * 20;

        cout << smoothie;
        for (int i = 1; i <= 5; i++) cout << ' ' << cnt[i];
        cout << ' ' << total << '\n';
    }
    return 0;
}
