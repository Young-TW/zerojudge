#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<unsigned long long> scores(N);
        for (int i = 0; i < N; ++i) {
            cin >> scores[i];
        }
        
        vector<unsigned long long> sorted_scores = scores;
        sort(sorted_scores.begin(), sorted_scores.end());
        
        vector<int> bit(N + 1, 0);
        
        for (int i = 0; i < N; ++i) {
            unsigned long long s = scores[i];
            int idx = lower_bound(sorted_scores.begin(), sorted_scores.end(), s) - sorted_scores.begin() + 1;
            
            for (int x = idx; x <= N; x += x & -x) {
                bit[x]++;
            }
            
            int less_count = 0;
            for (int x = idx - 1; x > 0; x -= x & -x) {
                less_count += bit[x];
            }
            
            cout << (i + 1) - less_count << "\n";
        }
    }
    
    return 0;
}
