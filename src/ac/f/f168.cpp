#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
long long target;
vector<int> v;

bool dfs(int idx, long long s1, long long s2, long long s3) {
    if (idx == N) {
        return s1 == target && s2 == target && s3 == target;
    }
    if (s1 + v[idx] <= target && dfs(idx + 1, s1 + v[idx], s2, s3)) return true;
    if (s2 + v[idx] <= target && s1 != s2 && dfs(idx + 1, s1, s2 + v[idx], s3)) return true;
    if (s3 + v[idx] <= target && s1 != s3 && s2 != s3 && dfs(idx + 1, s1, s2, s3 + v[idx])) return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> N) {
        v.resize(N);
        long long total_sum = 0;
        for (int i = 0; i < N; ++i) {
            cin >> v[i];
            total_sum += v[i];
        }

        if (total_sum % 3 != 0) {
            cout << "NO\n";
            continue;
        }

        target = total_sum / 3;
        sort(v.begin(), v.end(), greater<int>());
        
        if (dfs(0, 0, 0, 0)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
