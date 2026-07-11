#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long M, N, T;
    while (cin >> M >> N >> T) {
        long long total_height = 0;
        for (long long i = 0; i < T; ++i) {
            long long x, y, k;
            cin >> x >> y >> k;
            int cnt = 0;
            if (x > 1) cnt++;
            if (x < M) cnt++;
            if (y > 1) cnt++;
            if (y < N) cnt++;
            if (x > 1 && y > 1) cnt++;
            if (x > 1 && y < N) cnt++;
            if (x < M && y > 1) cnt++;
            if (x < M && y < N) cnt++;
            total_height += (long long)(cnt - 1) * k;
        }
        double avg = (double)total_height / (M * N);
        cout << fixed << setprecision(2) << avg << "\n";
    }
    return 0;
}
