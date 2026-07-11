#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int N;
        cin >> N;
        
        vector<vector<int>> pref_one(N, vector<int>(N));
        vector<vector<int>> pref_zero(N, vector<int>(N));
        vector<vector<int>> rank_zero(N, vector<int>(N + 1));
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int z;
                cin >> z;
                pref_one[i][j] = z - 1;
            }
        }
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int o;
                cin >> o;
                pref_zero[i][j] = o - 1;
                rank_zero[i][o - 1] = j;
            }
        }
        
        vector<int> match_one(N, -1);
        vector<int> match_zero(N, -1);
        vector<int> next_propose(N, 0);
        queue<int> free_one;
        
        for (int i = 0; i < N; ++i) {
            free_one.push(i);
        }
        
        while (!free_one.empty()) {
            int o = free_one.front();
            free_one.pop();
            
            int z = pref_one[o][next_propose[o]];
            next_propose[o]++;
            
            if (match_zero[z] == -1) {
                match_zero[z] = o;
                match_one[o] = z;
            } else {
                int current_o = match_zero[z];
                if (rank_zero[z][o] < rank_zero[z][current_o]) {
                    match_zero[z] = o;
                    match_one[o] = z;
                    match_one[current_o] = -1;
                    free_one.push(current_o);
                } else {
                    free_one.push(o);
                }
            }
        }
        
        for (int i = 0; i < N; ++i) {
            cout << i + 1 << " " << match_one[i] + 1 << "\n";
        }
    }
    
    return 0;
}
