#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    while (cin >> N) {
        if (N == 0) {
            cout << 0 << "\n";
            continue;
        }
        vector<int> A(N), B(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        for (int i = 0; i < N; ++i) {
            cin >> B[i];
        }
        
        unordered_map<int, int> pos;
        pos.reserve(N);
        for (int i = 0; i < N; ++i) {
            pos[B[i]] = i;
        }
        
        int C = 0;
        for (int i = 0; i < N - 1; ++i) {
            auto it1 = pos.find(A[i]);
            auto it2 = pos.find(A[i+1]);
            if (it1 != pos.end() && it2 != pos.end()) {
                if (it1->second + 1 == it2->second) {
                    C++;
                }
            }
        }
        
        cout << N - 1 - C << "\n";
    }
    return 0;
}
