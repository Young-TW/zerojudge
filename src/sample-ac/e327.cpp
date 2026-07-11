#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        int count = 0;
        for (char c : line) {
            if (c != ' ') {
                count++;
            }
        }
        if (count == 0) {
            cout << "\n";
        } else {
            cout << count << "\n";
        }
    }
    return 0;
}
