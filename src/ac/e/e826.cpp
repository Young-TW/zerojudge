#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        vector<int> gifts(N, 0);
        for (int i = 0; i < M; ++i) {
            int id, amount;
            cin >> id >> amount;
            gifts[id] += amount;
        }
        
        vector<int> idx(N);
        for (int i = 0; i < N; ++i) {
            idx[i] = i;
        }
        
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            if (gifts[a] != gifts[b]) {
                return gifts[a] > gifts[b];
            }
            return a < b;
        });
        
        for (int i = 0; i < N; ++i) {
            cout << idx[i] << " " << gifts[idx[i]] << "\n";
        }
    }
    
    return 0;
}
