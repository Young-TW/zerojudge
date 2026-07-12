#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        long long sum = 0;
        for (int i = 0; i < N; ++i) {
            long long x;
            cin >> x;
            sum += x;
            if (i > 0) cout << ' ';
            cout << sum;
        }
        cout << '\n';
    }
    
    return 0;
}
