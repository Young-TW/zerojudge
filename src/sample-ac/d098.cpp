#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        string word;
        long long sum = 0;
        while (iss >> word) {
            bool isNum = true;
            for (char c : word) {
                if (c < '0' || c > '9') {
                    isNum = false;
                    break;
                }
            }
            if (isNum) {
                long long val = 0;
                for (char c : word) {
                    val = val * 10 + (c - '0');
                }
                sum += val;
            }
        }
        cout << sum << "\n";
    }
    return 0;
}
