#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s && s != "#") {
        if (next_permutation(s.begin(), s.end())) {
            cout << s << "\n";
        } else {
            cout << "No Successor\n";
        }
    }
    
    return 0;
}
