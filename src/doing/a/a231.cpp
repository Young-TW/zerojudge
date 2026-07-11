#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 200005;
const int INF = 1e9 + 7;

struct Interval {
    int l, r, id;
};

int n;
Interval intervals[MAXN];
int dp[MAXN];
int next_idx[MAXN];
int sorted_by_r[MAXN];
int sorted_by_l[MAXN];

bool compareByR(int a, int b) {
    if (intervals[a].r != intervals[b].r)
        return intervals[a].r < intervals[b].r;
    return intervals[a].l < intervals[b].l;
}

bool compareByL(int a, int b) {
    if (intervals[a].l != intervals[b].l)
        return intervals[a].l < intervals[b].l;
    return intervals[a].r < intervals[b].r;
}

int findNext(int idx, int start_time) {
    int left = idx + 1;
    int right = n;
    int ans = n + 1;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        int real_idx = sorted_by_r[mid];
        if (intervals[real_idx].l >= start_time) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}

int main() {
    if (scanf("%d", &n) != 1) return 0;
    
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &intervals[i].l, &intervals[i].r);
        intervals[i].id = i;
        sorted_by_r[i] = i;
        sorted_by_l[i] = i;
    }
    
    sort(sorted_by_r + 1, sorted_by_r + n + 1, compareByR);
    sort(sorted_by_l + 1, sorted_by_l + n + 1, compareByL);
    
    for (int i = n; i >= 1; i--) {
        int idx = sorted_by_r[i];
        int next_pos = findNext(i, intervals[idx].r + 1);
        if (next_pos > n) {
            dp[i] = 1;
            next_idx[i] = n + 1;
        } else {
            dp[i] = 1 + dp[next_pos];
            next_idx[i] = next_pos;
        }
    }
    
    int max_meetings = 0;
    int start_pos = 1;
    for (int i = 1; i <= n; i++) {
        if (dp[i] > max_meetings) {
            max_meetings = dp[i];
            start_pos = i;
        }
    }
    
    printf("%d\n", max_meetings);
    
    vector<int> result;
    int current_pos = 1;
    int remaining = max_meetings;
    
    while (remaining > 0) {
        int best_choice = -1;
        int best_id = INF;
        
        for (int i = current_pos; i <= n; i++) {
            int idx = sorted_by_r[i];
            
            if (intervals[idx].l < (result.empty() ? 0 : intervals[result.back()].r + 1)) {
                continue;
            }
            
            int count_from_here = dp[i];
            if (count_from_here == remaining) {
                if (intervals[idx].id < best_id) {
                    best_id = intervals[idx].id;
                    best_choice = i;
                }
            }
        }
        
        if (best_choice == -1) break;
        
        result.push_back(sorted_by_r[best_choice]);
        remaining--;
        
        int next_start = intervals[sorted_by_r[best_choice]].r + 1;
        current_pos = findNext(best_choice, next_start);
    }
    
    sort(result.begin(), result.end(), [](int a, int b) {
        return intervals[a].id < intervals[b].id;
    });
    
    for (int i = 0; i < (int)result.size(); i++) {
        if (i > 0) printf(" ");
        printf("%d", intervals[result[i]].id);
    }
    printf("\n");
    
    return 0;
}
