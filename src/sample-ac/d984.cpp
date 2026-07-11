#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long a, b, c;
    while (cin >> a >> b >> c) {
        vector<pair<long long, char>> v = {{a, 'A'}, {b, 'B'}, {c, 'C'}};
        sort(v.begin(), v.end());
        
        if (v[2].first > v[1].first + v[0].first) {
            cout << v[2].second << "\n";
        } else {
            cout << v[1].second << "\n";
        }
    }
    
    return 0;
}
