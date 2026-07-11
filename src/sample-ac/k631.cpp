#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b;
    string var;
    char eq;
    
    while (cin >> a >> var >> eq >> b) {
        cout << var << " = " << b / a << "\n";
    }
    
    return 0;
}
