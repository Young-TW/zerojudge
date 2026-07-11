#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    if (!(cin >> n)) return 0;
    cin.ignore();
    
    int count = 0;
    string s;
    for (int i = 0; i < n; ++i) {
        if (!getline(cin, s)) break;
        if (s.find("商店") != string::npos) {
            ++count;
        }
    }
    
    cout << count << "\n";
    return 0;
}
