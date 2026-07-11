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
        string token;
        double ans = 0.0;
        bool hasData = false;
        
        while (ss >> token) {
            hasData = true;
            size_t pos = token.find(':');
            if (pos == string::npos) continue;
            
            int id = stoi(token.substr(0, pos));
            double val = stod(token.substr(pos + 1));
            
            if (id % 2 != 0) {
                ans += val;
            } else {
                ans -= val;
            }
        }
        
        if (hasData) {
            cout << ans << "\n";
        }
    }
    
    return 0;
}
