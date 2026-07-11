#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N, K;
            cin >> N >> K;
            unordered_map<int, int> pos;
            pos.reserve(N);
            for (int i = 1; i <= N; ++i) {
                int M;
                cin >> M;
                pos[M] = i;
            }
            for (int i = 0; i < K; ++i) {
                int L;
                cin >> L;
                cout << pos[L] << "\n";
            }
        }
    }
    
    return 0;
}
