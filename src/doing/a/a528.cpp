#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<string> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        sort(v.begin(), v.end(), [](const string &a, const string &b) {
            bool na = a[0] == '-', nb = b[0] == '-';
            if (na != nb) return na; // negative first
            if (na) { // both negative: reverse order
                string x = a.substr(1), y = b.substr(1);
                if (x.size() != y.size()) return x.size() > y.size();
                return x > y;
            }
            // both positive
            if (a.size() != b.size()) return a.size() < b.size();
            return a < b;
        });
        for (auto &s : v) cout << s << "\n";
    }
    return 0;
}
