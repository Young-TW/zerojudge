#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long N, E;
    while (cin >> N) {
        if (N == -1) break;
        cin >> E;
        long long days = 0;
        if (N > 0 && E > 0) {
            long long k = N;   // number of non-empty warehouses
            long long cur = N; // back-most non-empty warehouse
            long long r = E;   // food left in warehouse cur
            while (k > 0) {
                ++days;
                long long d = k; // today's quota = number of non-empty warehouses
                while (d > 0) {
                    if (r > d) {
                        r -= d;
                        d = 0;
                    } else {
                        d -= r;
                        --cur;
                        --k;
                        if (cur >= 1) r = E;
                    }
                }
            }
        }
        cout << days << '\n';
    }
    return 0;
}
