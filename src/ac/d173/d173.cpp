// d173 - 楓火看電影 (sliding-puzzle: move black tile from top-right corner
// to bottom-left corner, blank starts at bottom-left, whites fill the rest).
// Self-written. Answer = total number of tile slides (black + white).
//
// Modeled as a state (blank position, black position); white tiles are
// indistinguishable so this fully captures the puzzle. An independent BFS
// over these states gave: N=2:5, 3:13, 4:21, ... 9:61 -> closed form 8N-11.
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    while (cin >> N) {
        cout << (8 * N - 11) << '\n';
    }
    return 0;
}
