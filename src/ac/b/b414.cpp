#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

const int MAXN = 100010;
const int MAXM = 1000010;
const int BLOCK_SIZE = 320;

struct Query {
    int l, r, a, b, id;
    bool operator<(const Query& other) const {
        if (l / BLOCK_SIZE != other.l / BLOCK_SIZE)
            return l < other.l;
        return (l / BLOCK_SIZE & 1) ? r < other.r : r > other.r;
    }
};

int n, m;
int s[MAXN];
Query queries[MAXM];
int ans[MAXM];
int cnt[MAXN];
int block_cnt[BLOCK_SIZE + 5];
int current_ans;

void add(int x) {
    if (cnt[x] == 0) {
        current_ans++;
        block_cnt[x / BLOCK_SIZE]++;
    }
    cnt[x]++;
}

void remove(int x) {
    cnt[x]--;
    if (cnt[x] == 0) {
        current_ans--;
        block_cnt[x / BLOCK_SIZE]--;
    }
}

int query(int a, int b) {
    int res = 0;
    int start_block = a / BLOCK_SIZE;
    int end_block = b / BLOCK_SIZE;

    if (start_block == end_block) {
        for (int i = a; i <= b; i++) {
            if (cnt[i] > 0) res++;
        }
    } else {
        for (int i = a; i < (start_block + 1) * BLOCK_SIZE; i++) {
            if (cnt[i] > 0) res++;
        }
        for (int i = start_block + 1; i < end_block; i++) {
            res += block_cnt[i];
        }
        for (int i = end_block * BLOCK_SIZE; i <= b; i++) {
            if (cnt[i] > 0) res++;
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> queries[i].l >> queries[i].r >> queries[i].a >> queries[i].b;
        queries[i].id = i;
    }

    sort(queries, queries + m);

    int l = 1, r = 0;
    for (int i = 0; i < m; i++) {
        while (r < queries[i].r) add(s[++r]);
        while (r > queries[i].r) remove(s[r--]);
        while (l < queries[i].l) remove(s[l++]);
        while (l > queries[i].l) add(s[--l]);
        ans[queries[i].id] = query(queries[i].a, queries[i].b);
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
