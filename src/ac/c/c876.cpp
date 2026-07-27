#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int X, Y;
    while (cin >> X >> Y) {
        int a = X - 1, b = Y - 1;
        if (a > b) swap(a, b);
        int k = a / 3;
        int r = a % 3;
        bool win;
        int steps;
        if (r == 0) {
            win = false;
            steps = 2 * k;
        } else if (r == 1 && a == b) {
            win = false;
            steps = 2 * k;
        } else {
            win = true;
            steps = 2 * k + 1;
        }
        cout << (win ? "Win" : "Lose") << " " << steps << "\n";
    }
    return 0;
}
