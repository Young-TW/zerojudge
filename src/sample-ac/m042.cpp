#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

double get_weight(char c) {
    if (c == 'C') return 12.01;
    if (c == 'H') return 1.008;
    if (c == 'O') return 16.00;
    if (c == 'N') return 14.01;
    return 0.0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        string s;
        cin >> s;
        double total = 0.0;
        char current_elem = '\0';
        int count = 0;
        
        for (size_t i = 0; i < s.length(); ++i) {
            char c = s[i];
            if (c >= 'A' && c <= 'Z') {
                if (current_elem != '\0') {
                    if (count == 0) count = 1;
                    total += get_weight(current_elem) * count;
                }
                current_elem = c;
                count = 0;
            } else {
                count = count * 10 + (c - '0');
            }
        }
        
        if (current_elem != '\0') {
            if (count == 0) count = 1;
            total += get_weight(current_elem) * count;
        }
        
        cout << fixed << setprecision(3) << total + 1e-9 << "\n";
    }
    
    return 0;
}
