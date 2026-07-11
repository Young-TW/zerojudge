#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x;
    while (cin >> x) {
        char names[] = {'U', 'G', 'Y', 'T', 'I'};
        cout << names[x % 5] << '\n';
    }
    
    return 0;
}
