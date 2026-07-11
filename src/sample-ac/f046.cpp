#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int w, t;
    string m;
    while (cin >> w) {
        cin.ignore();
        getline(cin, m);
        cin >> t;
        string s = string(w, ' ') + m + string(w, ' ');
        cout << s.substr(t, w) << "\n";
    }
    return 0;
}
