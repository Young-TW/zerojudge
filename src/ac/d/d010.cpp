#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N;
    while (cin >> N) {
        long long sum = 0;
        for (long long i = 1; i * i <= N; ++i) {
            if (N % i == 0) {
                if (i != N) {
                    sum += i;
                }
                long long j = N / i;
                if (j != i && j != N) {
                    sum += j;
                }
            }
        }
        
        if (sum > N) {
            cout << "盈數\n";
        } else if (sum < N) {
            cout << "虧數\n";
        } else {
            cout << "完全數\n";
        }
    }
    
    return 0;
}
