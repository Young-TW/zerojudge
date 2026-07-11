#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> v(n);
        iota(v.begin(), v.end(), 1);
        do {
            for (int i = 0; i < n; ++i) {
                if (i > 0) cout << ' ';
                cout << v[i];
            }
            cout << '\n';
        } while (next_permutation(v.begin(), v.end()));
    }
    
    return 0;
}
