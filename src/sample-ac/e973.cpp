#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        vector<int> count(10, 0);
        for (char c : s) {
            count[c - '0']++;
        }
        
        vector<int> digits(10);
        for (int i = 0; i < 10; ++i) {
            digits[i] = i;
        }
        
        sort(digits.begin(), digits.end(), [&](int a, int b) {
            if (count[a] != count[b]) {
                return count[a] > count[b];
            }
            return a < b;
        });
        
        bool first = true;
        for (int i = 0; i < 10; ++i) {
            if (count[digits[i]] > 0) {
                if (!first) {
                    cout << " ";
                }
                cout << digits[i];
                first = false;
            }
        }
        cout << "\n";
    }
    
    return 0;
}
