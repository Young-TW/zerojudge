#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    if (!(cin >> N)) return 0;
    
    for (int i = 1; i <= N; ++i) {
        double sum = 0.0;
        double val;
        for (int j = 0; j < 12; ++j) {
            cin >> val;
            sum += val;
        }
        
        long long cents = llround(sum / 12.0 * 100.0);
        bool neg = cents < 0;
        if (neg) cents = -cents;
        
        long long dollars = cents / 100;
        long long frac = cents % 100;
        
        string s = to_string(dollars);
        string res = "";
        int len = s.length();
        for (int k = 0; k < len; ++k) {
            if (k > 0 && (len - k) % 3 == 0) {
                res += ',';
            }
            res += s[k];
        }
        
        cout << i << " $";
        if (neg) cout << "-";
        cout << res << ".";
        if (frac < 10) cout << "0";
        cout << frac << "\n";
    }
    
    return 0;
}
