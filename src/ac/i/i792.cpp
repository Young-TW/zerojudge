#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<long long> L(n);
        vector<long long> W(n);
        
        for (int i = 0; i < n; ++i) {
            cin >> L[i];
        }
        for (int i = 0; i < n; ++i) {
            cin >> W[i];
        }
        
        sort(L.begin(), L.end(), greater<long long>());
        
        long long current_sum = 0;
        long long total_energy = 0;
        
        for (int i = 0; i < n; ++i) {
            total_energy += current_sum * L[i];
            current_sum += W[i];
        }
        
        cout << total_energy << "\n";
    }
    
    return 0;
}
