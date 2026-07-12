#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

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

inline void writeInt(int x) {
    if (x == 0) {
        putchar('0');
        putchar('\n');
        return;
    }
    char buf[12];
    int p = 0;
    while (x) {
        buf[p++] = (x % 10) + '0';
        x /= 10;
    }
    while (p--) putchar(buf[p]);
    putchar('\n');
}

struct Query {
    int l, r, id;
};

int main() {
    int N, M;
    while (readInt(N)) {
        readInt(M);
        
        vector<vector<int>> pos(N + 1);
        for (int i = 1; i <= N; ++i) {
            int C;
            readInt(C);
            pos[C].push_back(i);
        }
        
        vector<vector<Query>> queries(N + 1);
        for (int i = 0; i < M; ++i) {
            int l, r, k;
            readInt(l);
            readInt(r);
            readInt(k);
            if (k <= N) {
                queries[k].push_back({l, r, i});
            }
        }
        
        vector<int> ans(M, 0);
        vector<int> current_idx;
        
        for (int k = 1; k <= N; ++k) {
            if (queries[k].empty()) continue;
            current_idx.clear();
            int total_size = 0;
            for (int v = k; v <= N; v += k) {
                total_size += pos[v].size();
            }
            current_idx.reserve(total_size);
            for (int v = k; v <= N; v += k) {
                current_idx.insert(current_idx.end(), pos[v].begin(), pos[v].end());
            }
            sort(current_idx.begin(), current_idx.end());
            
            for (const auto& q : queries[k]) {
                int l = q.l, r = q.r;
                int cnt = upper_bound(current_idx.begin(), current_idx.end(), r) - 
                          lower_bound(current_idx.begin(), current_idx.end(), l);
                ans[q.id] = cnt;
            }
        }
        
        for (int i = 0; i < M; ++i) {
            writeInt(ans[i]);
        }
    }
    
    return 0;
}
