#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, k;
    while (cin >> N >> k) {
        vector<int> a(N);
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
        }
        
        long long low = *max_element(a.begin(), a.end());
        long long high = accumulate(a.begin(), a.end(), 0LL);
        
        while (low < high) {
            long long mid = low + (high - low) / 2;
            long long current_sum = 0;
            int cards = 1;
            
            for (int x : a) {
                if (current_sum + x > mid) {
                    cards++;
                    current_sum = x;
                } else {
                    current_sum += x;
                }
            }
            
            if (cards <= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        
        cout << low << "\n";
    }
    
    return 0;
}
