#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    unsigned long long catalan[30];
    catalan[0] = 1;
    for (int i = 0; i < 26; ++i) {
        catalan[i + 1] = catalan[i] * 2 * (2 * i + 1) / (i + 2);
    }
    
    int n;
    while (cin >> n) {
        cout << catalan[n] << "\n";
    }
    
    return 0;
}
