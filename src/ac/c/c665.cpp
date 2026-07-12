#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string n;
    int b1, b2;
    while (cin >> n >> b1 >> b2) {
        vector<int> num;
        num.reserve(n.length());
        for (char c : n) {
            if (c >= '0' && c <= '9') num.push_back(c - '0');
            else if (c >= 'A' && c <= 'Z') num.push_back(c - 'A' + 10);
            else if (c >= 'a' && c <= 'z') num.push_back(c - 'a' + 10);
        }
        
        vector<int> ans;
        while (!num.empty()) {
            int rem = 0;
            vector<int> quotient;
            quotient.reserve(num.size());
            for (size_t i = 0; i < num.size(); ++i) {
                rem = rem * b1 + num[i];
                quotient.push_back(rem / b2);
                rem %= b2;
            }
            ans.push_back(rem);
            
            size_t start = 0;
            while (start < quotient.size() && quotient[start] == 0) {
                start++;
            }
            num.assign(quotient.begin() + start, quotient.end());
        }
        
        if (ans.empty()) {
            ans.push_back(0);
        }
        
        for (int i = (int)ans.size() - 1; i >= 0; --i) {
            if (ans[i] < 10) cout << (char)('0' + ans[i]);
            else cout << (char)('A' + ans[i] - 10);
        }
        cout << "\n";
    }
    
    return 0;
}
