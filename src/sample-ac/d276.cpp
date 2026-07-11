#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long N;
    while (cin >> N) {
        if (N < 0) {
            cout << "別鬧了  這明明很簡單\n";
            break;
        }
        if (N == 0) {
            cout << "Answer Is Too Big!\n";
        } else if (N == 1) {
            cout << "Nothing\n";
        } else {
            long long ans = N;
            for (long long i = 2; i * i <= N; ++i) {
                if (N % i == 0) {
                    ans = i;
                    while (N % i == 0) {
                        N /= i;
                    }
                }
            }
            if (N > 1) {
                ans = N;
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
