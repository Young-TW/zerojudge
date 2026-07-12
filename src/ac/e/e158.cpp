#include <cstdio>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

const int MAXN = 50005;
int bit[MAXN];
int parent[MAXN];

int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void update(int x, int n) {
    for (; x <= n; x += x & (-x))
        bit[x]++;
}

int query(int x) {
    int s = 0;
    for (; x > 0; x -= x & (-x))
        s += bit[x];
    return s;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        vector<tuple<int,int,int>> intervals(n);
        int maxB = 0;
        for (int i = 0; i < n; i++) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            intervals[i] = make_tuple(b, a, c);
            if (b > maxB) maxB = b;
        }
        sort(intervals.begin(), intervals.end());
        
        for (int i = 0; i <= maxB + 1; i++) {
            bit[i] = 0;
            parent[i] = i;
        }
        
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int b = get<0>(intervals[i]);
            int a = get<1>(intervals[i]);
            int c = get<2>(intervals[i]);
            int cnt = query(b) - query(a - 1);
            int need = c - cnt;
            if (need <= 0) continue;
            int pos = find(b);
            while (need > 0 && pos >= a) {
                update(pos, maxB);
                ans++;
                parent[pos] = find(pos - 1);
                pos = parent[pos];
                need--;
            }
        }
        
        printf("%d\n", ans);
    }
    return 0;
}
