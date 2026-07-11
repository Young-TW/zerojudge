#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const int MAXN = 200005;
int bit[MAXN];

void add(int idx, int val) {
    for (; idx < MAXN; idx += idx & -idx) {
        bit[idx] += val;
    }
}

int find_kth(int k) {
    int idx = 0;
    for (int i = 18; i >= 0; --i) {
        int next = idx + (1 << i);
        if (next < MAXN && bit[next] < k) {
            k -= bit[next];
            idx = next;
        }
    }
    return idx + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> ops;
    vector<int> vals;
    vector<int> params;

    string op;
    while (cin >> op) {
        if (op == "END") {
            break;
        }
        int param;
        cin >> param;
        ops.push_back(op);
        params.push_back(param);
        if (op == "GIVE") {
            vals.push_back(param);
        }
    }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    int total = 0;
    for (size_t i = 0; i < ops.size(); ++i) {
        if (ops[i] == "GIVE") {
            int idx = lower_bound(vals.begin(), vals.end(), params[i]) - vals.begin() + 1;
            add(idx, 1);
            total++;
        } else if (ops[i] == "FIND") {
            int k = params[i];
            int target = total - k + 1;
            int idx = find_kth(target);
            cout << vals[idx - 1] << "\n";
        }
    }

    return 0;
}
