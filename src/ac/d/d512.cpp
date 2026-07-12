#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<long long> arr(N);
        for (int i = 0; i < N; ++i) {
            cin >> arr[i];
        }
        
        vector<long long> sums;
        sums.reserve(1 << N);
        sums.push_back(0);
        for (int i = 0; i < N; ++i) {
            size_t sz = sums.size();
            for (size_t j = 0; j < sz; ++j) {
                sums.push_back(sums[j] + arr[i]);
            }
        }
        
        sort(sums.begin(), sums.end());
        sums.erase(unique(sums.begin(), sums.end()), sums.end());
        
        cout << sums.size() - 1 << "\n";
    }
    
    return 0;
}
