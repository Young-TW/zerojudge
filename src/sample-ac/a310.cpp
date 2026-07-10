#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Player {
    int score;
    int strength;
    int id;
};

int main() {
    int N, R, Q;
    while (cin >> N >> R >> Q) {
        int n2 = 2 * N;
        vector<Player> a(n2);
        for (int i = 0; i < n2; i++) {
            cin >> a[i].score;
            a[i].id = i + 1;
        }
        for (int i = 0; i < n2; i++) {
            cin >> a[i].strength;
        }
        auto better = [](const Player& x, const Player& y) {
            if (x.score != y.score) return x.score > y.score;
            return x.id < y.id;
        };
        sort(a.begin(), a.end(), better);
        vector<Player> win(n2), lose(n2), merged(n2);
        for (int r = 0; r < R; r++) {
            int wc = 0, lc = 0;
            for (int i = 0; i < n2; i += 2) {
                if (a[i].strength > a[i + 1].strength) {
                    a[i].score++;
                    win[wc++] = a[i];
                    lose[lc++] = a[i + 1];
                } else {
                    a[i + 1].score++;
                    win[wc++] = a[i + 1];
                    lose[lc++] = a[i];
                }
            }
            int i = 0, j = 0, k = 0;
            while (i < wc && j < lc) {
                if (better(win[i], lose[j])) merged[k++] = win[i++];
                else merged[k++] = lose[j++];
            }
            while (i < wc) merged[k++] = win[i++];
            while (j < lc) merged[k++] = lose[j++];
            swap(a, merged);
        }
        cout << a[Q - 1].id << "\n";
    }
    return 0;
}
