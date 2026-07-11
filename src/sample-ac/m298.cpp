#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        for (int t = 1; t <= T; ++t) {
            long long n;
            cin >> n;
            long long num = n * (n - 1);
            if (num % 4 == 0) {
                cout << "Case " << t << ": " << num / 4 << "\n";
            } else {
                cout << "Case " << t << ": " << num / 2 << "/2\n";
            }
        }
    }
    return 0;
}
