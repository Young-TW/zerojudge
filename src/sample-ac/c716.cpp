#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string name;
    while (cin >> name) {
        cout << "Go, " << name << ", go go\n";
    }
    
    return 0;
}
