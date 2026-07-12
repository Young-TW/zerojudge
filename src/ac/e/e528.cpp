#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            int cnt[10] = {0};
            for (int i = 1; i <= N; ++i) {
                int x = i;
                while (x > 0) {
                    cnt[x % 10]++;
                    x /= 10;
                }
            }
            for (int i = 0; i < 10; ++i) {
                cout << cnt[i] << (i == 9 ? '\n' : ' ');
            }
        }
    }
    
    return 0;
}
