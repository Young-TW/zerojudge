#include <iostream>
#include <string>
using namespace std;

int diff(const string &a, const string &b) {
    int d = 0;
    for (size_t i = 0; i < a.size(); ++i) if (a[i] != b[i]) ++d;
    return d;
}

int main() {
    int n;
    while (cin >> n) {
        while (n--) {
            string s;
            cin >> s;
            if (s.size() == 5) {
                cout << 3 << "\n";
            } else {
                int d1 = diff(s, "one");
                int d2 = diff(s, "two");
                cout << (d1 <= 1 ? 1 : 2) << "\n";
            }
        }
    }
    return 0;
}
