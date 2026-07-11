#include <iostream>
#include <vector>

using namespace std;

vector<long long> arr;
int n;
bool first = true;

void dfs(int idx, int depth) {
    if (idx >= n) return;
    dfs(idx * 2 + 2, depth + 1);
    if (!first) {
        cout << "\n";
    }
    first = false;
    for (int i = 0; i < 2 * depth + 1; ++i) {
        cout << " ";
    }
    cout << arr[idx] << "\n";
    dfs(idx * 2 + 1, depth + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long x;
    while (cin >> x) {
        arr.push_back(x);
    }
    n = arr.size();
    if (n > 0) {
        dfs(0, 0);
    }
    return 0;
}
