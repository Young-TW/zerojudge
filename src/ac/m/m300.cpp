#include <iostream>
#include <vector>

using namespace std;

vector<int> pre;
int idx;
int n;

void build_and_post(long long min_val, long long max_val) {
    if (idx >= n) return;
    long long val = pre[idx];
    if (val < min_val || val > max_val) return;
    idx++;
    build_and_post(min_val, val - 1);
    build_and_post(val + 1, max_val);
    cout << val << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int x;
    while (cin >> x) {
        pre.push_back(x);
    }
    
    n = pre.size();
    idx = 0;
    
    build_and_post(-1, 1000001);
    
    return 0;
}
