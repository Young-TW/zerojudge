#include <iostream>
#include <cmath>

using namespace std;

long long mul_mod(long long a, long long b, long long mod) {
    return (a * b) % mod;
}

long long pow_mod(long long a, long long p, long long mod) {
    long long res = 1;
    while (p > 0) {
        if (p & 1) res = mul_mod(res, a, mod);
        a = mul_mod(a, a, mod);
        p >>= 1;
    }
    return res;
}

struct HashTable {
    int head[1000003];
    int vis[1000003];
    int cur_time;
    struct Entry {
        long long key;
        long long val;
        int next;
    } entries[40005];
    int tot;
    
    void clear() {
        cur_time++;
        tot = 0;
    }
    
    void insert(long long key, long long val) {
        int h = key % 1000003;
        if (h < 0) h += 1000003;
        if (vis[h] != cur_time) {
            vis[h] = cur_time;
            head[h] = -1;
        }
        for (int i = head[h]; i != -1; i = entries[i].next) {
            if (entries[i].key == key) {
                entries[i].val = val;
                return;
            }
        }
        entries[tot].key = key;
        entries[tot].val = val;
        entries[tot].next = head[h];
        head[h] = tot++;
    }
    
    long long find(long long key) {
        int h = key % 1000003;
        if (h < 0) h += 1000003;
        if (vis[h] != cur_time) {
            return -1;
        }
        for (int i = head[h]; i != -1; i = entries[i].next) {
            if (entries[i].key == key) {
                return entries[i].val;
            }
        }
        return -1;
    }
} table;

long long bsgs(long long a, long long b, long long n) {
    a %= n;
    b %= n;
    if (b == 1) return 0;
    if (b == 0) return -1;
    
    long long m = (long long)sqrt((double)n);
    if (m * m < n) m++;
    
    table.clear();
    
    long long cur = b;
    for (long long j = 0; j < m; ++j) {
        table.insert(cur, j);
        cur = mul_mod(cur, a, n);
    }
    
    long long am = pow_mod(a, m, n);
    cur = am;
    for (long long i = 1; i <= m; ++i) {
        long long val = table.find(cur);
        if (val != -1) {
            return i * m - val;
        }
        cur = mul_mod(cur, am, n);
    }
    
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long a, b, n;
    while (cin >> a >> b >> n) {
        long long ans = bsgs(a, b, n);
        if (ans == -1) {
            cout << "NOT FOUND\n";
        } else {
            cout << ans << "\n";
        }
    }
    return 0;
}
