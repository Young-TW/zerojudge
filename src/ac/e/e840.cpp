#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int n = s.length();
        int e = 0, d = 0;
        
        for (char c : s) {
            if (isalpha(c)) {
                e++;
            } else if (isdigit(c)) {
                d++;
            }
        }
        
        int score = n * 3 + e * 3 + d * 2;
        
        if (e == n) {
            score -= n;
        }
        if (d == n) {
            score -= n;
        }
        
        for (int i = 1; i < n; ++i) {
            if (isdigit(s[i]) && isdigit(s[i - 1])) {
                score -= 2;
            }
        }
        
        bool meets_minimum = (n >= 8) && (e > 0) && (d > 0);
        if (meets_minimum) {
            score += 10;
        } else {
            score -= 5;
        }
        
        cout << score << "\n";
    }
    
    return 0;
}
