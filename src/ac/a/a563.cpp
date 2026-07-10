#include <cstdio>
#include <vector>
using namespace std;

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        vector<int> parent(n);
        parent[0] = -1;
        for (int i = 1; i < n; i++) {
            scanf("%d", &parent[i]);
        }
        // subtree sizes: process from high label to low (parent < child)
        vector<long long> sz(n, 1);
        for (int i = n - 1; i >= 1; i--) {
            sz[parent[i]] += sz[i];
        }
        // distance from root (parent < child => increasing order works)
        vector<long long> dist(n, 0);
        for (int i = 1; i < n; i++) {
            dist[i] = dist[parent[i]] + 1;
        }
        long long total = 0;
        for (int i = 0; i < n; i++) total += dist[i];
        // re-root: sumdist[child] = sumdist[parent] + n - 2*size[child]
        vector<long long> sumdist(n, 0);
        sumdist[0] = total;
        for (int i = 1; i < n; i++) {
            sumdist[i] = sumdist[parent[i]] + (long long)n - 2 * sz[i];
        }
        long long best = sumdist[0];
        int bestnode = 0;
        for (int i = 1; i < n; i++) {
            if (sumdist[i] < best) {
                best = sumdist[i];
                bestnode = i;
            }
        }
        printf("%d\n", bestnode);
    }
    return 0;
}
