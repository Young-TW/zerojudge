#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int coins[] = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
    int max_amount = 30000;
    vector<long long> dp(max_amount + 1, 0);
    dp[0] = 1;
    
    for (int c : coins) {
        for (int i = c; i <= max_amount; ++i) {
            dp[i] += dp[i - c];
        }
    }
    
    string s;
    while (cin >> s) {
        int amount = 0;
        bool dot_found = false;
        int decimal_places = 0;
        
        for (char c : s) {
            if (dot_found) {
                if (decimal_places < 2) {
                    amount = amount * 10 + (c - '0');
                    decimal_places++;
                }
            } else {
                if (c == '.') {
                    dot_found = true;
                } else {
                    amount = amount * 10 + (c - '0');
                }
            }
        }
        
        while (decimal_places < 2) {
            amount *= 10;
            decimal_places++;
        }
        
        if (amount == 0) break;
        
        double val = amount / 100.0;
        cout << setw(6) << fixed << setprecision(2) << val
             << setw(17) << dp[amount] << "\n";
    }
    
    return 0;
}
