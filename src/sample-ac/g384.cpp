#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int sum = 0;
        for (char c : s) {
            sum += c - 'A' + 1;
        }
        cout << sum << '\n';
    }
    
    return 0;
}
