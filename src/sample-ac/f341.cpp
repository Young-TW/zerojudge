#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string S, T;
    while (cin >> S >> T) {
        size_t pos = S.find(T);
        string L = S.substr(0, pos);
        string R = S.substr(pos + T.length());
        
        reverse(L.begin(), L.end());
        reverse(R.begin(), R.end());
        
        cout << R << T << L << "\n";
    }
    
    return 0;
}
