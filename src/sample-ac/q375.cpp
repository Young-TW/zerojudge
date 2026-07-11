#include <iostream>
#include <vector>
using namespace std;

long long countSubarrays(const vector<int>& arr, int L, int R) {
    long long count = 0;
    long long segLen = 0;
    int n = (int)arr.size();
    for (int i = 0; i < n; i++) {
        if (arr[i] >= L && arr[i] <= R) {
            segLen++;
        } else {
            count += segLen * (segLen + 1) / 2;
            segLen = 0;
        }
    }
    count += segLen * (segLen + 1) / 2;
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        int A, B;
        cin >> A >> B;
        vector<int> arr(N);
        for (int i = 0; i < N; i++) {
            cin >> arr[i];
        }
        
        long long ans = countSubarrays(arr, A, B) - countSubarrays(arr, A+1, B) 
                      - countSubarrays(arr, A, B-1) + countSubarrays(arr, A+1, B-1);
        
        cout << ans << "\n";
    }
    
    return 0;
}
