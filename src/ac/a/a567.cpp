#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

static int parent[10005];

static int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int main() {
    int N;
    while (scanf("%d", &N) == 1) {
        vector<pair<int,int>> jobs(N); // (profit, deadline)
        int maxd = 0;
        for (int i = 0; i < N; i++) {
            int d, p;
            scanf("%d %d", &d, &p);
            jobs[i] = make_pair(p, d);
            if (d > maxd) maxd = d;
        }
        for (int i = 0; i <= maxd; i++) parent[i] = i;
        sort(jobs.begin(), jobs.end(),
             [](const pair<int,int>& a, const pair<int,int>& b) {
                 return a.first > b.first;
             });
        long long total = 0;
        for (size_t i = 0; i < jobs.size(); i++) {
            int p = jobs[i].first, d = jobs[i].second;
            if (d > maxd) d = maxd;
            int slot = find(d);
            if (slot > 0) {
                total += p;
                parent[slot] = find(slot - 1);
            }
        }
        printf("%lld\n", total);
    }
    return 0;
}
