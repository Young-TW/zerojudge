#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int D;
    string N;
    
    while (cin >> D >> N) {
        if (D == 0 && N == "0") {
            break;
        }
        
        char d = D + '0';
        string ans = "";
        
        for (char c : N) {
            if (c != d) {
                ans += c;
            }
        }
        
        if (ans.empty()) {
            cout << "0\n";
        } else {
            size_t pos = ans.find_first_not_of('0');
            if (pos == string::npos) {
                cout << "0\n";
            } else {
                cout << ans.substr(pos) << "\n";
            }
        }
    }
    
    return 0;
}
