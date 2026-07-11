#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int parent[10005];
int rnk[10005];

void init(int n) {
    for (int i = 0; i <= n; ++i) {
        parent[i] = i;
        rnk[i] = 0;
    }
}

int find_set(int v) {
    int root = v;
    while (root != parent[root]) {
        root = parent[root];
    }
    while (v != root) {
        int next = parent[v];
        parent[v] = root;
        v = next;
    }
    return root;
}

bool union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rnk[a] < rnk[b])
            swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b])
            rnk[a]++;
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int M, N;
    while (cin >> M >> N) {
        init(M);
        int components = M + 1;
        string line;
        for (int i = 0; i < N; ++i) {
            getline(cin >> ws, line);
            stringstream ss(line);
            int u;
            if (ss >> u) {
                int v;
                while (ss >> v) {
                    if (union_sets(u, v)) {
                        components--;
                    }
                }
            }
        }
        getline(cin >> ws, line);
        stringstream ss(line);
        int k;
        if (ss >> k) {
            for (int i = 0; i < k; ++i) {
                int v;
                if (ss >> v) {
                    if (union_sets(0, v)) {
                        components--;
                    }
                }
            }
        }
        cout << components << "\n";
    }
    return 0;
}
