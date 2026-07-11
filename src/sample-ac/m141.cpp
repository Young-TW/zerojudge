#include <cstdio>

using namespace std;

const int MAX_NODES = 1000005;
int parent[MAX_NODES];

int find(int i) {
    return parent[i] == i ? i : (parent[i] = find(parent[i]));
}

void unite(int i, int j) {
    int rootI = find(i);
    int rootJ = find(j);
    if (rootI != rootJ) {
        parent[rootI] = rootJ;
    }
}

inline bool readInt(int &x) {
    x = 0;
    char c = getchar();
    while (c != EOF && (c < '0' || c > '9')) {
        c = getchar();
    }
    if (c == EOF) return false;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return true;
}

int main() {
    int N, M;
    while (readInt(N) && readInt(M)) {
        int V = N * M;
        for (int i = 0; i < V; ++i) {
            parent[i] = i;
        }
        
        long long E = 0;
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M - 1; ++j) {
                int s;
                readInt(s);
                if (s == 1) {
                    unite(i * M + j, i * M + j + 1);
                    E++;
                }
            }
        }
        
        for (int i = 0; i < N - 1; ++i) {
            for (int j = 0; j < M; ++j) {
                int t;
                readInt(t);
                if (t == 1) {
                    unite(i * M + j, (i + 1) * M + j);
                    E++;
                }
            }
        }
        
        int C = 0;
        for (int i = 0; i < V; ++i) {
            if (find(i) == i) {
                C++;
            }
        }
        
        long long ans = E - V + 2LL * C - 1;
        printf("%lld\n", ans);
    }
    
    return 0;
}
