#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
    while (cin >> N >> K && N != 0) {
        int nim_sum = 0;
        for (int i = 0; i < N; ++i) {
            long long P;
            cin >> P;
            nim_sum ^= (P % (K + 1));
        }
        if (nim_sum != 0) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}
