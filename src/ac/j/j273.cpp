#include <iostream>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        map<int, int> cnt;
        for (int i = 0; i < n; ++i) {
            int id;
            cin >> id;
            cnt[id]++;
        }
        for (map<int, int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
            cout << it->first << " " << it->second << "\n";
        }
    }
    
    return 0;
}
