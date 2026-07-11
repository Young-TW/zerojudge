#include <iostream>
#include <deque>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, w;
    while (cin >> n >> w) {
        if (n == 0 && w == 0) break;
        
        vector<int> m(n);
        for (int i = 0; i < n; i++) {
            cin >> m[i];
        }
        
        deque<int> maxDq, minDq;
        int bestDiff = INT_MAX;
        vector<int> results;
        
        for (int i = 0; i < n; i++) {
            while (!maxDq.empty() && m[maxDq.back()] <= m[i]) maxDq.pop_back();
            maxDq.push_back(i);
            
            while (!minDq.empty() && m[minDq.back()] >= m[i]) minDq.pop_back();
            minDq.push_back(i);
            
            int windowStart = i - w + 1;
            while (!maxDq.empty() && maxDq.front() < windowStart) maxDq.pop_front();
            while (!minDq.empty() && minDq.front() < windowStart) minDq.pop_front();
            
            if (i >= w - 1) {
                int diff = m[maxDq.front()] - m[minDq.front()];
                int start1 = windowStart + 1;
                if (diff < bestDiff) {
                    bestDiff = diff;
                    results.clear();
                    results.push_back(start1);
                } else if (diff == bestDiff) {
                    results.push_back(start1);
                }
            }
        }
        
        cout << results.size() << "\n";
        for (size_t i = 0; i < results.size(); i++) {
            cout << results[i] << " " << results[i] + w - 1 << "\n";
        }
    }
    
    return 0;
}
