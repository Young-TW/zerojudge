#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        int a, b, c;
        if (ss >> a >> b >> c) {
            cout << (a * 2 + b * 3 + c * 5) / 10 << "\n";
        } else {
            cout << "\n";
        }
    }
    return 0;
}
