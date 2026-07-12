#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    string c;
    if (!(cin >> a >> b >> c)) return 0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string line;
    while (getline(cin, line)) {
        string num_str;
        for (size_t i = 0; i <= line.size(); ++i) {
            if (i < line.size() && line[i] >= '0' && line[i] <= '9') {
                num_str += line[i];
            } else {
                if (!num_str.empty()) {
                    bool say = false;
                    char ca = a + '0';
                    char cb = b + '0';
                    if (num_str.find(ca) != string::npos || num_str.find(cb) != string::npos) {
                        say = true;
                    }
                    long long num = 0;
                    for (char nc : num_str) {
                        num = num * 10 + (nc - '0');
                    }
                    if (num % a == 0 || num % b == 0) {
                        say = true;
                    }
                    if (say) {
                        cout << c;
                    }
                    num_str.clear();
                }
            }
        }
        cout << "\n";
    }

    return 0;
}
