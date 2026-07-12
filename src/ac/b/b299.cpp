#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        long long min_w = 2147483648LL;
        for (int i = 0; i < M; ++i) {
            long long w;
            cin >> w;
            if (w < min_w) {
                min_w = w;
            }
        }
        if (N <= min_w) {
            cout << "YEEES!!! INKER!\n";
        } else {
            cout << "NOOOO!!! JACKY XX!\n";
        }
    }
    
    return 0;
}
