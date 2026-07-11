#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    cin.ignore();

    for (int t = 0; t < T; ++t) {
        string line;
        bool first_line = true;
        while (getline(cin, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line.empty()) {
                if (first_line) continue;
                else break;
            }
            if (!first_line) cout << "\n";
            first_line = false;
            for (char &c : line) {
                switch (c) {
                    case '0': c = 'O'; break;
                    case '1': c = 'I'; break;
                    case '2': c = 'Z'; break;
                    case '3': c = 'E'; break;
                    case '4': c = 'A'; break;
                    case '5': c = 'S'; break;
                    case '6': c = 'G'; break;
                    case '7': c = 'T'; break;
                    case '8': c = 'B'; break;
                    case '9': c = 'P'; break;
                }
            }
            cout << line;
        }
        if (t < T - 1) cout << "\n\n";
    }

    return 0;
}
