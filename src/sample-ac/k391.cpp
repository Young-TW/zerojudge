#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string name1, name2;
    int power1, power2;
    
    while (cin >> name1 >> power1 >> name2 >> power2) {
        if (power1 > power2) {
            cout << name1 << " WIN!\n";
        } else if (power2 > power1) {
            cout << name2 << " WIN!\n";
        } else {
            cout << "tie\n";
        }
    }
    
    return 0;
}
