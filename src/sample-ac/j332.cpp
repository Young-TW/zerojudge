#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        long long target;
        if (!(cin >> target)) break;
        
        long long count = 0;
        long long sum = 0;
        long long x;
        while (ss >> x) {
            if (x == target) {
                count++;
                sum += x;
            }
        }
        cout << count << "\n" << sum << "\n";
    }
    return 0;
}
