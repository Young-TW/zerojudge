#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            long long N, B;
            cin >> N >> B;
            long long total = 0;
            for (long long i = 0; i < B; ++i) {
                int K;
                cin >> K;
                long long box = 1;
                for (int j = 0; j < K; ++j) {
                    long long a;
                    cin >> a;
                    box = (box * (a % N)) % N;
                }
                total = (total + box) % N;
            }
            cout << total << "\n";
        }
    }
    
    return 0;
}
