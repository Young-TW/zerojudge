#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct BIT {
    vector<int> tree;
    int n;
    BIT(int n) : n(n), tree(n + 1, 0) {}
    void update(int i, int delta) {
        for (; i <= n; i += i & (-i))
            tree[i] += delta;
    }
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & (-i))
            sum += tree[i];
        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        vector<string> S(n);
        for (int i = 0; i < n; ++i) {
            cin >> S[i];
        }
        int q1, q2;
        cin >> q1 >> q2;
        vector<int> A(q1);
        for (int i = 0; i < q1; ++i) {
            cin >> A[i];
        }
        vector<int> B(q2);
        for (int i = 0; i < q2; ++i) {
            cin >> B[i];
        }

        vector<string> sorted_S = S;
        sort(sorted_S.begin(), sorted_S.end());
        
        for (int i = 0; i < q1; ++i) {
            string s = S[A[i] - 1];
            int pos = upper_bound(sorted_S.begin(), sorted_S.end(), s) - sorted_S.begin();
            int ans = n - pos + 1;
            if (i > 0) cout << " ";
            cout << ans;
        }
        cout << "\n";

        vector<string> temp = S;
        sort(temp.begin(), temp.end());
        temp.erase(unique(temp.begin(), temp.end()), temp.end());
        
        vector<int> val(n);
        for (int i = 0; i < n; ++i) {
            val[i] = lower_bound(temp.begin(), temp.end(), S[i]) - temp.begin() + 1;
        }
        
        vector<pair<int, int>> queries(q2);
        for (int i = 0; i < q2; ++i) {
            queries[i] = {B[i], i};
        }
        sort(queries.begin(), queries.end());
        
        BIT bit(temp.size());
        vector<int> ans2(q2);
        int ptr = 0;
        for (int i = 1; i <= n; ++i) {
            bit.update(val[i - 1], 1);
            while (ptr < q2 && queries[ptr].first == i) {
                int original_idx = queries[ptr].second;
                ans2[original_idx] = bit.query(val[i - 1] - 1);
                ptr++;
            }
        }
        
        for (int i = 0; i < q2; ++i) {
            if (i > 0) cout << " ";
            cout << ans2[i];
        }
        cout << "\n";
    }
    return 0;
}
