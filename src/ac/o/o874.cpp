#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

std::vector<int> ladj;
std::vector<signed char> grundy;

int solve(int mask) {
    if (grundy[mask] >= 0) return grundy[mask];
    int seen = 0;
    int mm = mask;
    while (mm) {
        int a = __builtin_ctz(mm);
        mm &= mm - 1;
        int avail = mask & ladj[a];
        // only consider b > a to avoid double counting
        avail &= ~((1 << (a + 1)) - 1);
        while (avail) {
            int b = __builtin_ctz(avail);
            avail &= avail - 1;
            int nmask = mask ^ (1 << a) ^ (1 << b);
            int g = solve(nmask);
            if (g < 31) seen |= (1 << g);
        }
    }
    int g = 0;
    while (seen & (1 << g)) g++;
    grundy[mask] = g;
    return g;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    while (std::cin >> n >> m) {
        std::vector<std::string> grid(n);
        for (int i = 0; i < n; ++i) std::cin >> grid[i];
        
        std::vector<std::pair<int,int>> pieces;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (grid[i][j] == '@') pieces.push_back({i, j});
        
        int k = pieces.size();
        
        std::vector<int> adj(k, 0);
        for (int i = 0; i < k; ++i) {
            for (int j = i+1; j < k; ++j) {
                int ddx = std::abs(pieces[i].first - pieces[j].first);
                int ddy = std::abs(pieces[i].second - pieces[j].second);
                if ((ddx==1 && ddy==2) || (ddx==2 && ddy==1)) {
                    adj[i] |= (1 << j);
                    adj[j] |= (1 << i);
                }
            }
        }
        
        // Find connected components
        std::vector<int> comp(k, -1);
        int numComp = 0;
        for (int i = 0; i < k; ++i) {
            if (comp[i] == -1) {
                comp[i] = numComp;
                std::vector<int> stk;
                stk.push_back(i);
                while (!stk.empty()) {
                    int u = stk.back(); stk.pop_back();
                    int nbrs = adj[u];
                    while (nbrs) {
                        int v = __builtin_ctz(nbrs);
                        nbrs &= nbrs - 1;
                        if (comp[v] == -1) {
                            comp[v] = numComp;
                            stk.push_back(v);
                        }
                    }
                }
                numComp++;
            }
        }
        
        int totalGrundy = 0;
        for (int c = 0; c < numComp; ++c) {
            std::vector<int> verts;
            for (int i = 0; i < k; ++i) if (comp[i] == c) verts.push_back(i);
            int s = verts.size();
            
            ladj.assign(s, 0);
            for (int i = 0; i < s; ++i) {
                for (int j = i+1; j < s; ++j) {
                    if (adj[verts[i]] & (1 << verts[j])) {
                        ladj[i] |= (1 << j);
                        ladj[j] |= (1 << i);
                    }
                }
            }
            
            grundy.assign(1 << s, -1);
            grundy[0] = 0;
            int g = solve((1 << s) - 1);
            totalGrundy ^= g;
        }
        
        if (totalGrundy != 0) std::cout << "Charlie\n";
        else std::cout << "Dave\n";
    }
    return 0;
}
