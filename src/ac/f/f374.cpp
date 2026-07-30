#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long K;
    string P;
    while (cin >> K >> P) {
        reverse(P.begin(), P.end());
        long long n = (long long)P.size();
        long long bestSum = -1, bestIdx = -1;
        for (long long i = 0; i < n; i += K) {
            long long sum = 0;
            for (long long j = i; j < i + K && j < n; ++j) {
                sum += P[j] - '0';
            }
            long long idx = i / K + 1;
            if (sum >= bestSum) {
                bestSum = sum;
                bestIdx = idx;
            }
        }
        cout << bestIdx << " " << bestSum << "\n";
    }
    return 0;
}
