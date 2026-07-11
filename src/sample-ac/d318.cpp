#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N;
    while (cin >> N) {
        if (N < 0) break;
        if (N == 0) {
            cout << "0\n";
            continue;
        }
        string ans;
        while (N > 0) {
            ans += (char)('0' + N % 3);
            N /= 3;
        }
        reverse(ans.begin(), ans.end());
        cout << ans << "\n";
    }
    
    return 0;
}
