#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string a;
    int n;
    
    while (cin >> a >> n) {
        if (n + 1 >= (int)a.length()) {
            cout << a << "\n";
        } else {
            cout << a.substr(0, n + 1) << "." << a.substr(n + 1) << "\n";
        }
    }
    
    return 0;
}
