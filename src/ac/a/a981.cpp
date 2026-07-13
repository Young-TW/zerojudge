#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
long long m;
vector<long long> arr;
vector<long long> suffix_sum;
vector<long long> current_path;
bool found;

void dfs(int index, long long current_sum) {
    if (current_sum == m) {
        found = true;
        for (size_t i = 0; i < current_path.size(); ++i) {
            cout << current_path[i] << (i == current_path.size() - 1 ? "" : " ");
        }
        cout << "\n";
        return;
    }
    if (index == n) return;
    
    if (current_sum + suffix_sum[index] < m) return;
    if (current_sum + arr[index] > m) return;
    
    current_path.push_back(arr[index]);
    dfs(index + 1, current_sum + arr[index]);
    current_path.pop_back();
    
    dfs(index + 1, current_sum);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> n >> m) {
        arr.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        sort(arr.begin(), arr.end());
        
        suffix_sum.resize(n);
        if (n > 0) {
            suffix_sum[n - 1] = arr[n - 1];
            for (int i = n - 2; i >= 0; --i) {
                suffix_sum[i] = suffix_sum[i + 1] + arr[i];
            }
        }
        
        current_path.clear();
        found = false;
        
        if (n > 0) {
            dfs(0, 0);
        }
        
        if (!found) {
            cout << "-1\n";
        }
    }
    
    return 0;
}
