#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n) {
        vector<string> v(n);
        for (int i = 0; i < n; ++i) {
            cin >> v[i];
        }
        sort(v.begin(), v.end(), [](const string& a, const string& b) {
            return a + b > b + a;
        });
        string ans;
        for (int i = 0; i < n; ++i) {
            ans += v[i];
        }
        cout << ans << "\n";
    }
    return 0;
}
