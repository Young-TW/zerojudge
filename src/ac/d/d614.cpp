#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    cin.ignore();
    string line;
    for (int t = 0; t < T; t++) {
        getline(cin, line);
        long long sum = 0;
        long long num = 0;
        bool inNum = false;
        for (size_t i = 0; i < line.size(); i++) {
            char c = line[i];
            if (c >= '0' && c <= '9') {
                num = num * 10 + (c - '0');
                inNum = true;
            } else {
                if (inNum) {
                    sum += num;
                    num = 0;
                    inNum = false;
                }
            }
        }
        if (inNum) sum += num;
        cout << sum << "\n";
    }
    return 0;
}
