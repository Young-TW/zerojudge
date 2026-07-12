#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    long long m;
    while (cin >> n >> m) {
        vector<int> v(n);
        for (int i = 0; i < n; ++i) {
            cin >> v[i];
        }
        sort(v.begin(), v.end(), greater<int>());
        
        long long sum = 0;
        int cnt = 0;
        bool found = false;
        for (int i = 0; i < n; ++i) {
            sum += v[i];
            cnt++;
            if (sum >= m) {
                found = true;
                break;
            }
        }
        
        if (found) {
            cout << cnt << "\n";
        } else {
            cout << "OAQ\n";
        }
    }
    
    return 0;
}
