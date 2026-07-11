#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<vector<int>> fact(1001);
    fact[0].push_back(1);
    for (int i = 1; i <= 1000; ++i) {
        vector<int> res = fact[i - 1];
        int carry = 0;
        for (size_t j = 0; j < res.size(); ++j) {
            int prod = res[j] * i + carry;
            res[j] = prod % 10;
            carry = prod / 10;
        }
        while (carry > 0) {
            res.push_back(carry % 10);
            carry /= 10;
        }
        fact[i] = res;
    }
    
    int n;
    while (cin >> n) {
        cout << n << "!\n";
        for (int i = fact[n].size() - 1; i >= 0; --i) {
            cout << fact[n][i];
        }
        cout << "\n";
    }
    
    return 0;
}
