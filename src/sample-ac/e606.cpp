#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    vector<int> X;
    while (cin >> n) {
        X.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> X[i];
        }
        sort(X.begin(), X.end());
        
        int left_idx = (n - 1) / 2;
        int right_idx = n / 2;
        
        int A = X[left_idx];
        int possible_A = X[right_idx] - X[left_idx] + 1;
        
        int count = upper_bound(X.begin(), X.end(), X[right_idx]) - 
                    lower_bound(X.begin(), X.end(), X[left_idx]);
                    
        cout << A << " " << count << " " << possible_A << "\n";
    }
    return 0;
}
