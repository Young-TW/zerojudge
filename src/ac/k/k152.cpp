#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string name1, name2;
    while (cin >> name1 >> name2) {
        cout << "|" << left << setw(10) << name1 << "|" << right << setw(10) << name2 << "|\n";
    }
    
    return 0;
}
