#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    cin.ignore();
    
    string line;
    for (int i = 0; i < T; ++i) {
        if (!getline(cin, line)) break;
        istringstream iss(line);
        long long sum = 0;
        int num;
        while (iss >> num) {
            sum += num;
        }
        cout << sum << "\n";
    }
    
    return 0;
}
