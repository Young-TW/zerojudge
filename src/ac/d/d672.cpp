#include <iostream>
#include <string>

using namespace std;

int digit_sum(int n) {
    int res = 0;
    while (n > 0) {
        res += n % 10;
        n /= 10;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s && s != "0") {
        int sum = 0;
        for (size_t i = 0; i < s.length(); ++i) {
            sum += (s[i] - '0');
        }
        
        if (sum % 9 != 0) {
            cout << s << " is not a multiple of 9.\n";
        } else {
            int degree = 1;
            while (sum > 9) {
                sum = digit_sum(sum);
                degree++;
            }
            cout << s << " is a multiple of 9 and has 9-degree " << degree << ".\n";
        }
    }
    
    return 0;
}
