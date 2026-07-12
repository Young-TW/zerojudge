#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// 檢查是否可以在最大負載為 k 的情況下，完成至少 ceil(N/2) 個作業
bool check(int k, int n, const vector<pair<int, int> >& jobs) {
    if (k == 0) return false;
    
    // 收集所有時間點並離散化
    vector<int> points;
    for (int i = 0; i < n; ++i) {
        points.push_back(jobs[i].first);
        points.push_back(jobs[i].second);
    }
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    
    int m = points.size();
    
    // 建立時間點到索引的映射
    map<int, int> point_to_idx;
    for (int i = 0; i < m; ++i) {
        point_to_idx[points[i]] = i;
    }
    
    // 使用差分数组來模擬每天的負載限制
    // diff[i] 表示在第 i 個時間區間開始時的負載變化
    vector<int> diff(m + 1, 0);
    vector<int> load(m, 0);
    
    int count = 0;
    
    // 按照結束時間排序作業，貪心地選擇作業
    vector<pair<int, int> > sorted_jobs = jobs;
    sort(sorted_jobs.begin(), sorted_jobs.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });
    
    for (int i = 0; i < n; ++i) {
        int s = sorted_jobs[i].first;
        int t = sorted_jobs[i].second;
        
        int s_idx = point_to_idx[s];
        int t_idx = point_to_idx[t];
        
        // 計算當前作業覆蓋的區間內的最大負載
        bool can_add = true;
        for (int j = s_idx; j < t_idx; ++j) {
            if (load[j] >= k) {
                can_add = false;
                break;
            }
        }
        
        if (can_add) {
            // 添加這個作業
            for (int j = s_idx; j < t_idx; ++j) {
                load[j]++;
            }
            count++;
        }
    }
    
    return count >= (n + 1) / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<pair<int, int> > jobs(n);
        for (int i = 0; i < n; ++i) {
            cin >> jobs[i].first >> jobs[i].second;
        }
        
        // 二分搜尋答案
        int left = 1, right = n;
        int ans = n;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (check(mid, n, jobs)) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
