#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int N;
vector<long long> d;
vector<long long> prefix_sum;
vector<vector<long long>> dp_min;

long long get_sum(int i, int j) {
    if (i > j) return 0;
    return prefix_sum[j + 1] - prefix_sum[i];
}

long long solve_min(int i, int j) {
    if (i > j) return 0;
    if (dp_min[i][j] != -1) return dp_min[i][j];
    
    long long root = d[i];
    long long best = LLONG_MAX;
    
    for (int k = i; k <= j; k++) {
        long long left_deg = solve_min(i + 1, k);
        long long right_deg = solve_min(k + 1, j);
        long long current = max(left_deg, right_deg) + root;
        if (current < best) {
            best = current;
        }
    }
    
    dp_min[i][j] = best;
    return best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> N) {
        if (N == 0) {
            cout << 0 << " " << 0 << "\n";
            continue;
        }
        d.resize(N);
        prefix_sum.resize(N + 1, 0);
        dp_min.assign(N, vector<long long>(N, -1));
        
        for (int i = 0; i < N; i++) {
            cin >> d[i];
            prefix_sum[i + 1] = prefix_sum[i] + d[i];
        }
        
        long long min_val = solve_min(0, N - 1);
        long long max_val = get_sum(0, N - 1);
        
        cout << min_val << " " << max_val << "\n";
    }
    
    return 0;
}
