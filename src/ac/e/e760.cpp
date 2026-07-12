#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <functional>
#include <cstring>

using namespace std;

const int MAX_STATES = 1 << 20;

long long dist[MAX_STATES];
char visited[MAX_STATES];
long long t[105];
int req[105], forb[105], add[105], rem[105];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    int case_num = 1;
    bool first = true;
    
    while (cin >> n >> m && (n || m)) {
        if (!first) cout << "\n";
        first = false;
        
        for (int i = 0; i < m; ++i) {
            string s1, s2;
            cin >> t[i] >> s1 >> s2;
            req[i] = forb[i] = add[i] = rem[i] = 0;
            for (int j = 0; j < n; ++j) {
                if (s1[j] == '+') req[i] |= (1 << j);
                else if (s1[j] == '-') forb[i] |= (1 << j);
                if (s2[j] == '+') add[i] |= (1 << j);
                else if (s2[j] == '-') rem[i] |= (1 << j);
            }
        }
        
        int start_state = (1 << n) - 1;
        int target_state = 0;
        int num_states = 1 << n;
        
        memset(dist, -1, num_states * sizeof(long long));
        memset(visited, 0, num_states * sizeof(char));
        
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        
        dist[start_state] = 0;
        pq.push({0, start_state});
        
        while (!pq.empty()) {
            pair<long long, int> top = pq.top();
            pq.pop();
            long long d = top.first;
            int u = top.second;
            
            if (visited[u]) continue;
            visited[u] = 1;
            
            if (u == target_state) break;
            
            for (int i = 0; i < m; ++i) {
                if ((u & req[i]) == req[i] && (u & forb[i]) == 0) {
                    int v = (u | add[i]) & ~rem[i];
                    if (dist[v] == -1 || dist[v] > d + t[i]) {
                        dist[v] = d + t[i];
                        pq.push({dist[v], v});
                    }
                }
            }
        }
        
        cout << "Product " << case_num++ << "\n";
        if (dist[target_state] == -1) {
            cout << "Bugs cannot be fixed.\n";
        } else {
            cout << "Fastest sequence takes " << dist[target_state] << " seconds.\n";
        }
    }
    
    return 0;
}
