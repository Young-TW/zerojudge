#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    for (int t = 0; t < T; ++t) {
        string plain, cipher;
        while (getline(cin, plain) && plain.empty());
        getline(cin, cipher);

        if (t > 0) {
            cout << "\n";
        }

        cout << cipher << "\n";
        cout << plain << "\n";

        char mp[256];
        for (int i = 0; i < 256; ++i) {
            mp[i] = (char)i;
        }
        for (size_t i = 0; i < plain.size(); ++i) {
            mp[(unsigned char)plain[i]] = cipher[i];
        }

        string line;
        while (getline(cin, line)) {
            if (line.empty()) break;
            for (size_t i = 0; i < line.size(); ++i) {
                cout << mp[(unsigned char)line[i]];
            }
            cout << "\n";
        }
    }

    return 0;
}
