#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<pair<long long, long long>> fort;
        fort.reserve(N);
        for (int i = 0; i < N; i++) {
            long long a, b;
            cin >> a >> b;
            if (a == 0 && b == 0) continue; // takes 0 time regardless of position
            fort.push_back({a, b});
        }
        
        // Sort by a/b ascending (i before j iff a_i * b_j < a_j * b_i)
        sort(fort.begin(), fort.end(), [](const pair<long long,long long>& x, const pair<long long,long long>& y) {
            return x.first * y.second < y.first * x.second;
        });
        
        const long long M = 100000007LL;
        long long t = 0;
        for (size_t i = 0; i < fort.size(); i++) {
            long long a = fort[i].first;
            long long b = fort[i].second;
            // strength at time t = a + b*t; new t = t + strength = a + (1+b)*t
            t = (a + (1 + b) * t) % M;
        }
        
        cout << t << "\n";
    }
    
    return 0;
}
