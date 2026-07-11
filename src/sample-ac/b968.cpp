#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string girl, boy;
    while (cin >> girl >> boy) {
        cout << girl << " and " << boy << " sitting in the tree\n";
    }
    
    return 0;
}
