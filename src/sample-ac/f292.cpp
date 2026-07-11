#include <cstdio>

const int MAXN = 100005;
const int MAXM = 200005;

int parent[MAXM];
int sz[MAXM];
long long sum[MAXM];
int id[MAXN];

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) == 2) {
        for (int i = 1; i <= N; ++i) {
            id[i] = i;
            parent[i] = i;
            sz[i] = 1;
            sum[i] = i;
        }
        int cnt = N;
        for (int i = 0; i < M; ++i) {
            int op;
            if (scanf("%d", &op) != 1) break;
            if (op == 1) {
                int P, Q;
                scanf("%d %d", &P, &Q);
                int rootP = find(id[P]);
                int rootQ = find(id[Q]);
                if (rootP != rootQ) {
                    parent[rootP] = rootQ;
                    sz[rootQ] += sz[rootP];
                    sum[rootQ] += sum[rootP];
                }
            } else if (op == 2) {
                int P, Q;
                scanf("%d %d", &P, &Q);
                int rootP = find(id[P]);
                int rootQ = find(id[Q]);
                if (rootP != rootQ) {
                    sz[rootP]--;
                    sum[rootP] -= P;
                    cnt++;
                    id[P] = cnt;
                    parent[cnt] = rootQ;
                    sz[cnt] = 1;
                    sum[cnt] = P;
                    sz[rootQ]++;
                    sum[rootQ] += P;
                }
            } else if (op == 3) {
                int P;
                scanf("%d", &P);
                int rootP = find(id[P]);
                printf("%d %lld\n", sz[rootP], sum[rootP]);
            }
        }
    }
    return 0;
}
