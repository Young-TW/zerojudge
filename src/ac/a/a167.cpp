#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 5005 * 2;

struct SAM {
    int len[MAXN];
    int link[MAXN];
    int next[MAXN][256];
    int sz;
    int last;
    long long ans;

    void init() {
        len[0] = 0;
        link[0] = -1;
        memset(next[0], 0, sizeof(next[0]));
        sz = 1;
        last = 0;
        ans = 0;
    }

    void extend(int c) {
        int cur = sz++;
        len[cur] = len[last] + 1;
        memset(next[cur], 0, sizeof(next[cur]));
        
        int p = last;
        while (p != -1 && !next[p][c]) {
            next[p][c] = cur;
            p = link[p];
        }
        
        if (p == -1) {
            link[cur] = 0;
        } else {
            int q = next[p][c];
            if (len[p] + 1 == len[q]) {
                link[cur] = q;
            } else {
                int clone = sz++;
                len[clone] = len[p] + 1;
                memcpy(next[clone], next[q], sizeof(next[q]));
                link[clone] = link[q];
                while (p != -1 && next[p][c] == q) {
                    next[p][c] = clone;
                    p = link[p];
                }
                link[q] = link[cur] = clone;
            }
        }
        
        ans += len[cur] - len[link[cur]];
        last = cur;
    }
};

SAM sam;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        while (T--) {
            string s;
            cin >> s;
            sam.init();
            for (size_t i = 0; i < s.length(); ++i) {
                sam.extend((unsigned char)s[i]);
            }
            cout << sam.ans << "\n";
        }
    }
    return 0;
}
