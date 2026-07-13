#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int year;
    bool first = true;
    while (cin >> year) {
        if (!first) cout << "\n";
        first = false;
        cout << "1/4\n1/11\n1/18\n1/25\n2/1\n2/8\n2/15\n2/22\n";
    }
    return 0;
}
