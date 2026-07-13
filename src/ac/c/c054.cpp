#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <functional>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string kb = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
    char mapping[256];
    for (int i = 0; i < 256; ++i) {
        mapping[i] = ' ';
    }
    mapping[' '] = ' ';
    for (size_t i = 1; i < kb.size(); ++i) {
        mapping[(unsigned char)kb[i]] = kb[i - 1];
    }

    string line;
    while (getline(cin, line)) {
        for (char c : line) {
            cout << mapping[(unsigned char)c];
        }
        cout << '\n';
    }

    return 0;
}
