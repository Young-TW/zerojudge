#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

long long dp[100005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T, N;
    if (!(cin >> T >> N)) return 0;
    
    vector<string> names(N);
    vector<long long> M(N);
    vector<int> H(N);
    
    long long best_M = -1;
    int best_H = 1;
    string best_job;
    
    vector<vector<long long>> jobs_by_H(T + 1);
    
    for (int i = 0; i < N; ++i) {
        cin >> names[i] >> M[i] >> H[i];
        if (M[i] * best_H > best_M * H[i]) {
            best_M = M[i];
            best_H = H[i];
            best_job = names[i];
        }
        if (H[i] <= T) {
            jobs_by_H[H[i]].push_back(M[i]);
        }
    }
    
    vector<pair<int, long long>> filtered_jobs;
    for (int h = 1; h <= T; ++h) {
        if (jobs_by_H[h].empty()) continue;
        auto& ms = jobs_by_H[h];
        sort(ms.rbegin(), ms.rend());
        int max_count = T / h;
        for (int i = 0; i < (int)ms.size() && i < max_count; ++i) {
            filtered_jobs.push_back({h, ms[i]});
        }
    }
    
    for (int i = 0; i <= T; ++i) dp[i] = 0;
    
    for (auto& job : filtered_jobs) {
        int h = job.first;
        long long m = job.second;
        for (int j = T; j >= h; --j) {
            if (dp[j - h] + m > dp[j]) {
                dp[j] = dp[j - h] + m;
            }
        }
    }
    
    long long ans = 0;
    for (int i = 0; i <= T; ++i) {
        if (dp[i] > ans) ans = dp[i];
    }
    
    cout << ans << "\n" << best_job << "\n";
    
    return 0;
}
