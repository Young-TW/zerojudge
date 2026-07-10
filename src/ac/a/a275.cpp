#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string a, b;
    while (cin >> a) {
        if (a == "STOP!!") break;
        cin >> b;
        if (b == "STOP!!") break;
        if (a.size() != b.size()) {
            cout << "no\n";
            continue;
        }
        int cnt[128] = {0};
        for (char c : a) cnt[(unsigned char)c]++;
        for (char c : b) cnt[(unsigned char)c]--;
        bool ok = true;
        for (int i = 0; i < 128; i++) {
            if (cnt[i] != 0) { ok = false; break; }
        }
        cout << (ok ? "yes" : "no") << "\n";
    }
    return 0;
}
