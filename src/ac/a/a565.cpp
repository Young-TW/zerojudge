#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (!(cin >> n)) return 0;
    string s;
    while (n-- > 0) {
        cin >> s;
        long long bal = 0, ans = 0;
        for (char c : s) {
            if (c == 'p') {
                bal++;
            } else if (c == 'q') {
                if (bal > 0) {
                    bal--;
                    ans++;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
