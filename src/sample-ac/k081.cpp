#include <cstdio>
#include <vector>
#include <queue>

const int BUF_SIZE = 1 << 20;
char buf[BUF_SIZE], *p1 = buf, *p2 = buf;
inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, BUF_SIZE, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

template <typename T>
inline bool readInt(T &x) {
    char c = gc();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == EOF) return false;
        c = gc();
    }
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = gc();
    }
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    if (neg) x = -x;
    return true;
}

int main() {
    int n;
    while (readInt(n)) {
        int blocks = (n + 63) / 64;
        std::vector<unsigned long long> adj((size_t)n * blocks, 0);
        std::vector<unsigned long long> unvisited(blocks, 0);
        
        for (int i = 0; i < n; ++i) {
            unvisited[i / 64] |= (1ULL << (i % 64));
            for (int j = 0; j < n; ++j) {
                int x;
                readInt(x);
                if (x) {
                    adj[(size_t)i * blocks + (j / 64)] |= (1ULL << (j % 64));
                }
            }
        }
        
        int a, b;
        long long k;
        readInt(a);
        readInt(b);
        readInt(k);
        
        if (a == b) {
            printf("0\nYou did it ! You did it !\n");
            continue;
        }
        
        std::queue<int> q;
        std::vector<int> dist(n, -1);
        
        dist[a] = 0;
        q.push(a);
        unvisited[a / 64] &= ~(1ULL << (a % 64));
        
        bool found = false;
        while (!q.empty() && !found) {
            int u = q.front();
            q.pop();
            
            for (int i = 0; i < blocks; ++i) {
                unsigned long long mask = adj[(size_t)u * blocks + i] & unvisited[i];
                while (mask) {
                    int j = __builtin_ctzll(mask);
                    mask &= (mask - 1);
                    int v = i * 64 + j;
                    
                    dist[v] = dist[u] + 1;
                    if (v == b) {
                        if (dist[v] <= k) {
                            printf("%d\nYou did it ! You did it !\n", dist[v]);
                        } else {
                            printf("You failed the mission and pooped on pants !\n");
                        }
                        found = true;
                        break;
                    }
                    q.push(v);
                    unvisited[i] &= ~(1ULL << j);
                }
                if (found) break;
            }
        }
        
        if (!found) {
            printf("You failed the mission and pooped on pants !\n");
        }
    }
    return 0;
}
