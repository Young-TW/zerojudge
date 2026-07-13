#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<long long> spices(N);
        for (int i = 0; i < N; i++) cin >> spices[i];
        
        int M, K;
        cin >> M >> K;
        
        unordered_map<long long, pair<int, int> > pos;
        
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < K; j++) {
                long long v;
                cin >> v;
                if (pos.find(v) == pos.end()) {
                    pos[v] = make_pair(i + 1, j + 1);
                }
            }
        }
        
        for (int i = 0; i < N; i++) {
            unordered_map<long long, pair<int, int> >::iterator it = pos.find(spices[i]);
            if (it == pos.end()) {
                cout << -1 << "\n";
            } else {
                cout << it->second.first << " " << it->second.second << "\n";
            }
        }
    }
    
    return 0;
}
