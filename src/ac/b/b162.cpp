#include <iostream>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        map<long long, int> cnt;
        for (int i = 0; i < n; ++i) {
            long long x;
            cin >> x;
            cnt[x]++;
        }
        for (map<long long, int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
            cout << it->first << " " << it->second << "\n";
        }
    }
    
    return 0;
}
