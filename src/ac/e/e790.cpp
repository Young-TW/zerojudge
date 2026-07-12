#include <iostream>

using namespace std;

void solve(long long n, long long i, int from, int to, int via) {
    if (n == 1) {
        cout << "move " << n << " from " << from << " to " << to << "\n";
        return;
    }
    long long half = 1LL << (n - 1);
    if (i < half) {
        solve(n - 1, i, from, via, to);
    } else if (i == half) {
        cout << "move " << n << " from " << from << " to " << to << "\n";
    } else {
        solve(n - 1, i - half, via, to, from);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long N, i;
    while (cin >> N >> i) {
        solve(N, i, 1, 3, 2);
    }
    return 0;
}
