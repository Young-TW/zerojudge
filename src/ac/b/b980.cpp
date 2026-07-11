#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<int> red_packets;
        int x;
        while (cin >> x) {
            if (x == -1) break;
            red_packets.push_back(x);
        }
        
        sort(red_packets.begin(), red_packets.end(), greater<int>());
        
        long long total = 0;
        int limit = min(N, static_cast<int>(red_packets.size()));
        for (int i = 0; i < limit; ++i) {
            total += red_packets[i];
        }
        
        cout << total << "\n";
    }
    
    return 0;
}
