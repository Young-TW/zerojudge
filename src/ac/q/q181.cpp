#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int a, b;
    while (cin >> a >> b) {
        int n;
        cin >> n;
        long long total_wait = 0;
        for (int i = 0; i < n; ++i) {
            int t;
            cin >> t;
            int cycle = a + b;
            int remainder = t % cycle;
            if (remainder >= a) {
                total_wait += (cycle - remainder);
            }
        }
        cout << total_wait << "\n";
    }
    
    return 0;
}
