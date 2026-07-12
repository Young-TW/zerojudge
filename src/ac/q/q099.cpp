#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstring>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<string> words(N);
        for (int i = 0; i < N; ++i) {
            cin >> words[i];
        }
        
        bool present[256] = {false};
        vector<int> adj[256];
        int in_degree[256] = {0};
        bool edge[256][256] = {false};
        
        for (const string& w : words) {
            for (char ch : w) {
                unsigned char uc = static_cast<unsigned char>(ch);
                present[uc] = true;
            }
        }
        
        for (int i = 0; i < N - 1; ++i) {
            const string& w1 = words[i];
            const string& w2 = words[i+1];
            int len = min(w1.size(), w2.size());
            int j = 0;
            while (j < len && w1[j] == w2[j]) {
                ++j;
            }
            if (j < len) {
                unsigned char c1 = static_cast<unsigned char>(w1[j]);
                unsigned char c2 = static_cast<unsigned char>(w2[j]);
                if (!edge[c1][c2]) {
                    edge[c1][c2] = true;
                    adj[c1].push_back(c2);
                    in_degree[c2]++;
                }
            }
        }
        
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int c = 0; c < 256; ++c) {
            if (present[c] && in_degree[c] == 0) {
                pq.push(c);
            }
        }
        
        string result;
        while (!pq.empty()) {
            int u = pq.top();
            pq.pop();
            result.push_back(static_cast<char>(u));
            for (int v : adj[u]) {
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    pq.push(v);
                }
            }
        }
        
        cout << result << '\n';
    }
    
    return 0;
}
