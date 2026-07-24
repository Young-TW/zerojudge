#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

long long solve(int m, vector<int>& digits) {
    sort(digits.begin(), digits.end(), greater<int>());
    
    int n1, n2;
    if (m % 2 == 0) {
        n1 = m / 2;
        n2 = m / 2;
    } else {
        n1 = m / 2;
        n2 = m / 2 + 1;
    }
    
    long long max_val = -1;
    
    vector<int> idx(m);
    for (int i = 0; i < m; i++) idx[i] = i;
    
    do {
        long long num1 = 0;
        for (int i = 0; i < n1; i++) {
            num1 = num1 * 10 + digits[idx[i]];
        }
        
        long long num2 = 0;
        for (int i = n1; i < m; i++) {
            num2 = num2 * 10 + digits[idx[i]];
        }
        
        long long prod = num1 * num2;
        if (prod > max_val) {
            max_val = prod;
        }
    } while (next_permutation(idx.begin(), idx.end()));
    
    return max_val;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m;
    while (cin >> m) {
        vector<int> digits(m);
        for (int i = 0; i < m; i++) {
            cin >> digits[i];
        }
        cout << solve(m, digits) << "\n";
    }
    
    return 0;
}
