#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    const int MAX_N = 100000;
    const int MAX_SUM = MAX_N + 9 * 5;
    int ans[MAX_SUM + 1] = {0};
    
    for (int i = 1; i <= MAX_N; ++i) {
        int sum = i;
        int temp = i;
        while (temp > 0) {
            sum += temp % 10;
            temp /= 10;
        }
        if (sum <= MAX_SUM && ans[sum] == 0) {
            ans[sum] = i;
        }
    }
    
    int T;
    if (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            cout << ans[N] << "\n";
        }
    }
    
    return 0;
}
