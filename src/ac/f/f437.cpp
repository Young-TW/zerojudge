#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <functional>
#include <numeric>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int M, N;
            cin >> M >> N;
            vector<vector<int>> count(N, vector<int>(4, 0));
            
            for (int i = 0; i < M; ++i) {
                string s;
                cin >> s;
                for (int j = 0; j < N; ++j) {
                    int idx;
                    if (s[j] == 'A') idx = 0;
                    else if (s[j] == 'C') idx = 1;
                    else if (s[j] == 'G') idx = 2;
                    else idx = 3; // 'T'
                    count[j][idx]++;
                }
            }
            
            string consensus = "";
            int total_error = 0;
            
            for (int j = 0; j < N; ++j) {
                int max_count = -1;
                int best_idx = 0;
                for (int k = 0; k < 4; ++k) {
                    if (count[j][k] > max_count) {
                        max_count = count[j][k];
                        best_idx = k;
                    }
                }
                
                if (best_idx == 0) consensus += 'A';
                else if (best_idx == 1) consensus += 'C';
                else if (best_idx == 2) consensus += 'G';
                else consensus += 'T';
                
                total_error += (M - max_count);
            }
            
            cout << consensus << "\n";
            cout << total_error << "\n";
        }
    }
    
    return 0;
}
