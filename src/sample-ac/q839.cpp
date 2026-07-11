#include <iostream>

using namespace std;

int parent[505];
int rank_[505];
int D[505][505];

void init_dsu(int n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank_[i] = 0;
    }
}

int find(int i) {
    int root = i;
    while (parent[root] != root) {
        root = parent[root];
    }
    while (parent[i] != root) {
        int next = parent[i];
        parent[i] = root;
        i = next;
    }
    return root;
}

void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        if (rank_[root_i] < rank_[root_j]) {
            parent[root_i] = root_j;
        } else if (rank_[root_i] > rank_[root_j]) {
            parent[root_j] = root_i;
        } else {
            parent[root_j] = root_i;
            rank_[root_i]++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    while (cin >> n >> k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> D[i][j];
            }
        }
        
        auto check = [&](int X) {
            init_dsu(n);
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    if (D[i][j] < X) {
                        unite(i, j);
                    }
                }
            }
            int components = 0;
            for (int i = 0; i < n; ++i) {
                if (find(i) == i) {
                    components++;
                }
            }
            return components >= k;
        };
        
        int low = 0, high = 100000001;
        while (low < high) {
            int mid = low + (high - low + 1) / 2;
            if (check(mid)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        cout << low << "\n";
    }
    return 0;
}
