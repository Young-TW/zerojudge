#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int count_ways(long long N) {
    if (N == 0) return 1;
    N = abs(N);
    int count = 0;
    for (long long k = 1; k * (k + 1) <= 2 * N; ++k) {
        if ((2 * N) % k != 0) continue;
        long long temp = (2 * N) / k - k - 1;
        if (temp >= 0 && temp % 2 == 0) {
            ++count;
        }
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    while (cin >> N) {
        cout << count_ways(N) << '\n';
    }
    return 0;
}
