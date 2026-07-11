#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
    while (cin >> N >> K) {
        vector<int> arr(N);
        for (int i = 0; i < N; ++i) {
            cin >> arr[i];
        }
        
        int left = 0;
        int non_2_count = 0;
        int max_len = 0;
        
        for (int right = 0; right < N; ++right) {
            if (arr[right] != 2) {
                non_2_count++;
            }
            
            while (non_2_count > K) {
                if (arr[left] != 2) {
                    non_2_count--;
                }
                left++;
            }
            
            max_len = max(max_len, right - left + 1);
        }
        
        cout << max_len << "\n";
    }
    
    return 0;
}
