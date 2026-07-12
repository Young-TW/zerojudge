#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<long long> pos;
    pos.push_back(0);
    pos.push_back(1);
    int m = 1;
    for (int i = 2; ; ++i) {
        while (m < (int)pos.size() && pos[m] < i) {
            m++;
        }
        long long next_pos = pos.back() + m;
        pos.push_back(next_pos);
        if (next_pos >= 2000000000LL) {
            break;
        }
    }
    
    long long n;
    while (cin >> n && n != 0) {
        int ans = lower_bound(pos.begin(), pos.end(), n) - pos.begin();
        cout << ans << "\n";
    }
    
    return 0;
}
