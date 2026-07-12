#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> get_prime_factors(int n) {
    vector<int> factors;
    int temp = n;
    for (int i = 2; i * i <= temp; ++i) {
        if (temp % i == 0) {
            factors.push_back(i);
            while (temp % i == 0) {
                temp /= i;
            }
        }
    }
    if (temp > 1 && temp != n) {
        factors.push_back(temp);
    }
    return factors;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int s, t;
    int case_num = 1;
    
    while (cin >> s >> t && (s || t)) {
        if (s == t) {
            cout << "Case " << case_num++ << ": 0\n";
            continue;
        }
        if (s > t) {
            cout << "Case " << case_num++ << ": -1\n";
            continue;
        }
        
        vector<int> dist(t + 1, -1);
        queue<int> q;
        q.push(s);
        dist[s] = 0;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            vector<int> factors = get_prime_factors(u);
            for (int f : factors) {
                int v = u + f;
                if (v <= t && dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        
        cout << "Case " << case_num++ << ": " << dist[t] << "\n";
    }
    
    return 0;
}
