#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> a(n);
        unordered_set<int> s;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            s.insert(a[i]);
        }
        
        unordered_set<int> valid_sums;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int sum = a[i] + a[j];
                if (s.count(sum)) {
                    valid_sums.insert(sum);
                }
            }
        }
        
        cout << valid_sums.size() << "\n";
    }
    
    return 0;
}
