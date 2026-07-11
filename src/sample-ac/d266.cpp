#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        // 計算 2^n - 1
        vector<int> num;
        num.push_back(1);
        
        for (int i = 0; i < n; i++) {
            int carry = 0;
            for (size_t j = 0; j < num.size(); j++) {
                int val = num[j] * 2 + carry;
                num[j] = val % 10;
                carry = val / 10;
            }
            while (carry) {
                num.push_back(carry % 10);
                carry /= 10;
            }
        }
        
        // 減 1
        int idx = 0;
        while (num[idx] == 0) {
            num[idx] = 9;
            idx++;
        }
        num[idx]--;
        
        // 去除前導零
        while (num.size() > 1 && num.back() == 0) {
            num.pop_back();
        }
        
        for (int j = (int)num.size() - 1; j >= 0; j--) {
            cout << num[j];
        }
        cout << "\n";
    }
    
    return 0;
}
