#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
    while (cin >> N >> K) {
        vector<pair<int, int>> arr(N);
        for (int i = 0; i < N; ++i) {
            cin >> arr[i].first >> arr[i].second;
        }
        
        sort(arr.begin(), arr.end());
        
        priority_queue<int> pq;
        long long min_vol = -1;
        
        for (int i = 0; i < N; ++i) {
            pq.push(arr[i].second);
            if ((int)pq.size() > K) {
                pq.pop();
            }
            if ((int)pq.size() == K) {
                long long r = arr[i].first;
                long long h = pq.top();
                long long vol = 4 * r * r * h;
                if (min_vol == -1 || vol < min_vol) {
                    min_vol = vol;
                }
            }
        }
        
        cout << min_vol << "\n";
    }
    
    return 0;
}
