#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b;
    while (cin >> a >> b) {
        if (a == 0 && b == 0) break;
        
        vector<long long> arr(a);
        for (int i = 0; i < a; ++i) {
            cin >> arr[i];
        }
        
        map<long long, int> sum_counts;
        vector<int> mask(a, 0);
        for (int i = 0; i < b; ++i) {
            mask[a - 1 - i] = 1;
        }
        
        do {
            long long current_sum = 0;
            for (int i = 0; i < a; ++i) {
                if (mask[i]) {
                    current_sum += arr[i];
                }
            }
            sum_counts[current_sum]++;
        } while (next_permutation(mask.begin(), mask.end()));
        
        long long best_sum = -1;
        int best_cnt = -1;
        
        for (auto& p : sum_counts) {
            if (p.second > best_cnt) {
                best_cnt = p.second;
                best_sum = p.first;
            }
        }
        
        cout << best_sum << " " << best_cnt << "\n";
    }
    
    return 0;
}
