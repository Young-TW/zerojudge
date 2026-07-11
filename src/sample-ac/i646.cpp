#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n != 0) {
        string s;
        for (int i = 0; i < n; ++i) {
            s += static_cast<char>('a' + i);
        }
        do {
            cout << s << "\n";
        } while (next_permutation(s.begin(), s.end()));
    }
    
    return 0;
}
