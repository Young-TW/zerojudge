#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int R, N;
    while (cin >> R >> N) {
        int temp;
        for (int i = 0; i < N; ++i) {
            cin >> temp;
        }
        long long total_seconds = (2LL * N + R) / (2 * R);
        cout << total_seconds / 60 << ":" << setfill('0') << setw(2) << total_seconds % 60 << "\n";
    }
    return 0;
}
