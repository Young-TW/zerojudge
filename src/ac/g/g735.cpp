#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> scores(n);
        for (int i = 0; i < n; ++i) {
            cin >> scores[i];
        }
        
        vector<int> sorted_scores = scores;
        sort(sorted_scores.begin(), sorted_scores.end(), greater<int>());
        
        for (int i = 0; i < n; ++i) {
            int rank = lower_bound(sorted_scores.begin(), sorted_scores.end(), scores[i], greater<int>()) - sorted_scores.begin() + 1;
            if (i > 0) cout << " ";
            cout << rank;
        }
        cout << "\n";
    }
    
    return 0;
}
