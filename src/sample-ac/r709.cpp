#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void print_int128(__int128 x) {
    if (x == 0) {
        cout << '0';
        return;
    }
    string s = "";
    while (x > 0) {
        s += char('0' + (int)(x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long N;
    while (cin >> N) {
        __int128 ans = (__int128)N * (N + 1) * (N + 2) * (3 * N + 1) / 12;
        print_int128(ans);
        cout << "\n";
    }
    
    return 0;
}
