#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    char c;
    int n;
    while (cin >> c >> n) {
        cout << c << setw(3) << setfill('0') << n << '\n';
    }
    
    return 0;
}
