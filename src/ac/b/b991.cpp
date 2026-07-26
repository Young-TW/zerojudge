#include <iostream>
#include <unordered_map>
#include <cstdint>

using namespace std;

using int64 = long long;

// ---------- k = 2 ----------
int friunlde2(int64 n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;
    if (n & 1)   return 0;          // odd >=3
    return 1;                       // even >=4
}

// ---------- k = 1 ----------
unordered_map<int64, int> memo1;

int friunlde1(int64 n) {
    auto it = memo1.find(n);
    if (it != memo1.end()) return it->second;

    int ans;
    if (n == 0) ans = 0;
    else if (n == 1) ans = 1;
    else if (n == 2) ans = 0;
    else if (n == 3) ans = 1;
    else if (n == 4) ans = 2;
    else if (n == 5) ans = 0;
    else if (n == 6) ans = 2;
    else if (n == 7) ans = 0;
    else if (n & 1)   ans = 0;               // odd >=5
    else {
        int half = friunlde1(n >> 1);        // n is even and >=8
        ans = (half == 1) ? 2 : 1;
    }
    memo1[n] = ans;
    return ans;
}

// ---------- main ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int64 n;
    int k;
    while (cin >> n >> k) {
        if (k == 1) cout << friunlde1(n) << '\n';
        else        cout << friunlde2(n) << '\n';
    }
    return 0;
}
