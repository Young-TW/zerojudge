#include <iostream>
#include <string>

using namespace std;

void solve(const string& records, int target) {
    int w = 0, l = 0;
    for (char c : records) {
        if (c == 'W') {
            w++;
        } else if (c == 'L') {
            l++;
        }
        
        if ((w >= target || l >= target) && (w - l >= 2 || l - w >= 2)) {
            cout << w << ":" << l << "\n";
            w = 0;
            l = 0;
        }
    }
    cout << w << ":" << l << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string records;
    char c;
    while (cin >> c) {
        if (c == 'E') break;
        if (c == 'W' || c == 'L') {
            records += c;
        }
    }
    
    solve(records, 11);
    cout << "\n";
    solve(records, 21);
    
    return 0;
}
