#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        map<int, int> mp;
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            int val = (s[3] - '0') * 10 + (s[4] - '0');
            mp[val]++;
        }
        for (const auto& p : mp) {
            cout << p.first << " " << p.second << "\n";
        }
    }
    
    return 0;
}
