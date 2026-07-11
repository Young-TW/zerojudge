#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<long long> A(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            cin >> A[i];
        }
        long long sum = 0;
        long long x, y;
        while (cin >> x >> y) {
            if (x == 0 && y == 0) break;
            if (x >= 1 && x <= N) {
                sum += A[x] * y;
            }
        }
        cout << sum << "\n";
    }
    return 0;
}
