#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        if (w != other.w) return w < other.w;
        if (u != other.u) return u < other.u;
        return v < other.v;
    }
};

int parent[26];
int rank_[26];

int find_set(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find_set(parent[i]);
}

void union_set(int i, int j) {
    int root_i = find_set(i);
    int root_j = find_set(j);
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

    int T;
    if (cin >> T) {
        for (int t = 1; t <= T; ++t) {
            int N;
            cin >> N;
            vector<Edge> edges;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    int val;
                    cin >> val;
                    if (j < N - 1) {
                        char comma;
                        cin >> comma;
                    }
                    if (i < j && val > 0) {
                        edges.push_back({i, j, val});
                    }
                }
            }

            sort(edges.begin(), edges.end());

            for (int i = 0; i < N; ++i) {
                parent[i] = i;
                rank_[i] = 0;
            }

            vector<Edge> mst;
            for (const auto& e : edges) {
                if (find_set(e.u) != find_set(e.v)) {
                    union_set(e.u, e.v);
                    mst.push_back(e);
                }
            }

            cout << "Case " << t << ":\n";
            for (const auto& e : mst) {
                cout << (char)('A' + e.u) << "-" << (char)('A' + e.v) << " " << e.w << "\n";
            }
        }
    }
    return 0;
}
