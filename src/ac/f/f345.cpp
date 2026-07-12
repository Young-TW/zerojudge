#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    if (!(cin >> n)) return 0;
    
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    
    if (n > 0) {
        cout << v[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            cout << ' ' << v[i];
        }
    }
    cout << '\n';
    
    return 0;
}
