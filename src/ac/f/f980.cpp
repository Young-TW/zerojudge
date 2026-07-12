#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string n_str;
    long long P;
    
    while (cin >> n_str >> P) {
        long long n_int = 0;
        bool too_large = false;
        
        for (size_t i = 0; i < n_str.length(); ++i) {
            n_int = n_int * 10 + (n_str[i] - '0');
            if (n_int > 100000) {
                too_large = true;
                break;
            }
        }
        
        if (too_large || n_int >= P) {
            cout << 0 << "\n";
        } else {
            long long ans = 1;
            for (long long i = 2; i <= n_int; ++i) {
                ans = (ans * i) % P;
            }
            cout << ans << "\n";
        }
    }
    
    return 0;
}
