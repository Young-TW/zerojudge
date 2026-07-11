#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<long long> x(n);
        for (int i = 0; i < n; ++i) {
            cin >> x[i];
        }
        
        if (n == 0) {
            cout << 0 << "\n";
            continue;
        }
        
        int i = 0, j = n - 1;
        long long prefix_sum = x[0], suffix_sum = x[n - 1];
        int count = 0;
        
        while (i < n && j >= 0) {
            if (prefix_sum == suffix_sum) {
                count++;
                i++;
                j--;
                if (i < n) prefix_sum += x[i];
                if (j >= 0) suffix_sum += x[j];
            } else if (prefix_sum < suffix_sum) {
                i++;
                if (i < n) prefix_sum += x[i];
            } else {
                j--;
                if (j >= 0) suffix_sum += x[j];
            }
        }
        
        cout << count << "\n";
    }
    
    return 0;
}
