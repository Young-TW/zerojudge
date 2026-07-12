#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

vector<pair<int, int>> solve(int N) {
    int total = 2 * N;
    int max_val = 4 * N;
    vector<bool> is_prime = sieve(max_val);

    vector<int> match(total, -1);
    vector<bool> used(total, false);

    for (int i = 0; i < total; ++i) {
        if (match[i] != -1) continue;
        for (int j = i + 1; j < total; ++j) {
            if (match[j] != -1) continue;
            if (is_prime[4 * N - i - j]) {
                match[i] = j;
                match[j] = i;
                break;
            }
        }
    }

    vector<pair<int, int>> edges;
    for (int i = 0; i < total; ++i) {
        if (i < match[i]) {
            edges.emplace_back(i, match[i]);
        }
    }

    sort(edges.begin(), edges.end());
    return edges;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;
        vector<pair<int, int>> edges = solve(N);
        for (const auto& edge : edges) {
            cout << edge.first << " " << edge.second << "\n";
        }
    }
    return 0;
}
