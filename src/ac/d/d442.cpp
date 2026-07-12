#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (cin >> T) {
        for (int i = 1; i <= T; ++i) {
            int N;
            if (cin >> N) {
                int n = N;
                while (n != 1 && n != 4) {
                    int sum = 0;
                    while (n > 0) {
                        int d = n % 10;
                        sum += d * d;
                        n /= 10;
                    }
                    n = sum;
                }
                if (n == 1) {
                    cout << "Case #" << i << ": " << N << " is a Happy number.\n";
                } else {
                    cout << "Case #" << i << ": " << N << " is an Unhappy number.\n";
                }
            }
        }
    }
    return 0;
}
