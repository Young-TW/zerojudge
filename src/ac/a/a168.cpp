#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 5005;
struct Node {
    int len, link;
    int next[26];
    int cnt;
} st[MAXN * 2];

int sz, last;

void sam_init() {
    sz = 1;
    last = 0;
    st[0].len = 0;
    st[0].link = -1;
    st[0].cnt = 0;
    for (int i = 0; i < 26; ++i) st[0].next[i] = 0;
}

void sam_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].link = -1;
    st[cur].cnt = 1;
    for (int i = 0; i < 26; ++i) st[cur].next[i] = 0;
    
    int p = last;
    while (p != -1 && !st[p].next[c]) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].link = st[q].link;
            for (int i = 0; i < 26; ++i) st[clone].next[i] = st[q].next[i];
            st[clone].cnt = 0;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = clone;
            st[cur].link = clone;
        }
    }
    last = cur;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            string s;
            cin >> s;
            sam_init();
            for (char ch : s) {
                sam_extend(ch - 'a');
            }
            
            vector<int> order(sz);
            for (int i = 0; i < sz; ++i) order[i] = i;
            sort(order.begin(), order.end(), [](int a, int b) {
                return st[a].len < st[b].len;
            });
            
            for (int i = sz - 1; i >= 0; --i) {
                int v = order[i];
                if (st[v].link != -1) {
                    st[st[v].link].cnt += st[v].cnt;
                }
            }
            
            int max_len = 0;
            for (int i = 1; i < sz; ++i) {
                if (st[i].cnt >= 2) {
                    max_len = max(max_len, st[i].len);
                }
            }
            cout << max_len << "\n";
        }
    }
    return 0;
}
