#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        cin.ignore();
        vector<string> names(n);
        for (int i = 0; i < n; ++i) {
            getline(cin, names[i]);
        }
        sort(names.begin(), names.end(), [](const string& a, const string& b) {
            if (a.length() != b.length()) {
                return a.length() < b.length();
            }
            return a < b;
        });
        for (int i = 0; i < n; ++i) {
            cout << names[i] << '\n';
        }
    }
    
    return 0;
}
