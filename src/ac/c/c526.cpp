#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <climits>
using namespace std;

vector<int> current_path;
vector<bool> used;
vector<vector<int>> adj;
int L, R;
bool found;

void dfs(int node) {
    if (found) return;
    if (current_path.size() == R - L + 1) {
        found = true;
        return;
    }
    for (int neighbor : adj[node]) {
        if (!used[neighbor]) {
            used[neighbor] = true;
            current_path.push_back(neighbor);
            dfs(neighbor);
            if (found) return;
            current_path.pop_back();
            used[neighbor] = false;
        }
    }
}

int main() {
    int max_n = 300;
    vector<vector<int>> square_pairs(max_n + 1);

    for (int i = 1; i <= max_n; ++i) {
        for (int j = i + 1; j <= max_n; ++j) {
            int sum = i + j;
            int root = sqrt(sum);
            if (root * root == sum) {
                square_pairs[i].push_back(j);
                square_pairs[j].push_back(i);
            }
        }
    }

    while (cin >> L >> R) {
        int n = R - L + 1;
        if (n == 1) {
            cout << -1 << endl;
            continue;
        }

        adj.assign(n, vector<int>());
        for (int i = 0; i < n; ++i) {
            int num1 = L + i;
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                int num2 = L + j;
                int sum = num1 + num2;
                int root = sqrt(sum);
                if (root * root == sum) {
                    adj[i].push_back(j);
                }
            }
        }

        found = false;
        vector<int> best_path;
        for (int start = 0; start < n && !found; ++start) {
            current_path.clear();
            current_path.push_back(start);
            used.assign(n, false);
            used[start] = true;
            dfs(start);
            if (found) {
                best_path = current_path;
                break;
            }
        }

        if (!found) {
            cout << -1 << endl;
        } else {
            for (int i = 0; i < best_path.size(); ++i) {
                if (i != 0) cout << " ";
                cout << L + best_path[i];
            }
            cout << endl;
        }
    }
    return 0;
}
