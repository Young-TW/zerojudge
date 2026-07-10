#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;


int main() {
    int U, L;
    while (cin >> U >> L) {
        vector<long long> up(U), lo(L);
        for (int i = 0; i < U; i++) cin >> up[i];
        for (int i = 0; i < L; i++) cin >> lo[i];
        const long long INF = LLONG_MAX / 4;
        vector<long long> prev(L + 1, 0), cur(L + 1, 0);
        for (int i = 1; i <= U; i++) {
            cur[0] = INF;
            for (int j = 1; j <= L; j++) {
                long long cost = prev[j - 1] + llabs(up[i - 1] - lo[j - 1]);
                long long skip = cur[j - 1];
                cur[j] = min(cost, skip);
            }
            swap(prev, cur);
        }
        cout << prev[L] << "\n";
    }
    return 0;
}
