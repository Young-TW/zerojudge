#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string n;
    int k;
    while (cin >> n >> k) {
        bool graph[10][10] = {false};
        for (int i = 0; i < 10; ++i) {
            graph[i][i] = true;
        }
        for (int i = 0; i < k; ++i) {
            int u, v;
            cin >> u >> v;
            graph[u][v] = true;
        }
        for (int l = 0; l < 10; ++l) {
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    if (graph[i][l] && graph[l][j]) {
                        graph[i][j] = true;
                    }
                }
            }
        }

        int cnt[10] = {0};
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (graph[i][j]) {
                    cnt[i]++;
                }
            }
        }

        vector<int> res;
        res.push_back(1);
        for (char c : n) {
            int d = c - '0';
            int multiplier = cnt[d];
            if (multiplier == 0) multiplier = 1; 
            int carry = 0;
            for (size_t i = 0; i < res.size(); ++i) {
                int prod = res[i] * multiplier + carry;
                res[i] = prod % 10;
                carry = prod / 10;
            }
            while (carry) {
                res.push_back(carry % 10);
                carry /= 10;
            }
        }

        for (int i = res.size() - 1; i >= 0; --i) {
            cout << res[i];
        }
        cout << "\n";
    }
    return 0;
}
