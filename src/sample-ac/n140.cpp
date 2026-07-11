#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

int fact[8] = {1, 1, 2, 6, 24, 120, 720, 5040};
int dist[20160];

int get_rank(int a[8]) {
    int rank = 0;
    int count[7] = {0};
    for (int i = 0; i < 8; ++i) count[a[i]]++;
    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < a[i]; ++j) {
            if (count[j] > 0) {
                int remaining_zeros = count[0] - (j == 0 ? 1 : 0);
                rank += fact[7 - i] / fact[remaining_zeros];
            }
        }
        count[a[i]]--;
    }
    return rank;
}

void unrank(int rank, int a[8]) {
    int count[7] = {0};
    count[0] = 2;
    for (int i = 1; i <= 6; ++i) count[i] = 1;
    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j <= 6; ++j) {
            if (count[j] == 0) continue;
            
            int remaining_zeros = count[0] - (j == 0 ? 1 : 0);
            int perm = fact[7 - i] / fact[remaining_zeros];
            
            if (rank < perm) {
                a[i] = j;
                count[j]--;
                break;
            } else {
                rank -= perm;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    memset(dist, -1, sizeof(dist));
    
    int target[8] = {1, 2, 3, 4, 5, 6, 0, 0};
    int target_rank = get_rank(target);
    dist[target_rank] = 0;
    
    queue<int> q;
    q.push(target_rank);
    
    vector<int> adj[8] = {
        {1, 4},
        {0, 2, 5},
        {1, 3, 6},
        {2, 7},
        {0, 5},
        {1, 4, 6},
        {2, 5, 7},
        {3, 6}
    };
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        int a[8];
        unrank(u, a);
        
        int p1 = -1, p2 = -1;
        for (int i = 0; i < 8; ++i) {
            if (a[i] == 0) {
                if (p1 == -1) p1 = i;
                else p2 = i;
            }
        }
        
        for (int p : {p1, p2}) {
            for (int nxt : adj[p]) {
                if (a[nxt] != 0) {
                    swap(a[p], a[nxt]);
                    int v = get_rank(a);
                    if (dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        q.push(v);
                    }
                    swap(a[p], a[nxt]);
                }
            }
        }
    }
    
    int val;
    while (cin >> val) {
        int grid[16];
        grid[0] = val;
        for (int i = 1; i < 16; ++i) {
            cin >> grid[i];
        }
        
        int a2[8];
        for (int i = 8; i < 16; ++i) {
            int num = grid[i];
            if (num == 0) a2[i - 8] = 0;
            else a2[i - 8] = num - 8;
        }
        
        cout << dist[get_rank(a2)] << "\n";
    }
    
    return 0;
}
