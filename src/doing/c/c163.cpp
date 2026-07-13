#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        set<int> sums;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                sums.insert(a[i] + a[j]);
            }
        }
        
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (sums.find(a[i]) != sums.end()) {
                count++;
            }
        }
        
        cout << count << "\n";
    }
    
    return 0;
}
