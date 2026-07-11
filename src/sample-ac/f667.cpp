#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x;
    while (cin >> x) {
        vector<int> v;
        while (x != -1) {
            v.push_back(x);
            cin >> x;
        }
        int k;
        cin >> k;
        sort(v.begin(), v.end(), greater<int>());
        cout << v[k - 1] << "\n";
    }
    
    return 0;
}
