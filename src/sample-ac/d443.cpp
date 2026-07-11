#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> add(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    int carry = 0;
    for (size_t i = 0; i < max(a.size(), b.size()) || carry; ++i) {
        int sum = carry;
        if (i < a.size()) sum += a[i];
        if (i < b.size()) sum += b[i];
        res.push_back(sum % 10);
        carry = sum / 10;
    }
    return res;
}

vector<int> mul(const vector<int>& a, int b) {
    vector<int> res;
    int carry = 0;
    for (size_t i = 0; i < a.size() || carry; ++i) {
        long long prod = carry;
        if (i < a.size()) prod += (long long)a[i] * b;
        res.push_back(prod % 10);
        carry = prod / 10;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<vector<int>> D(805);
    D[1] = {0};
    D[2] = {1};
    for (int i = 3; i <= 800; ++i) {
        vector<int> sum = add(D[i-1], D[i-2]);
        D[i] = mul(sum, i - 1);
    }
    
    int n;
    while (cin >> n) {
        if (n == -1) break;
        for (int i = D[n].size() - 1; i >= 0; --i) {
            cout << D[n][i];
        }
        cout << "\n";
    }
    
    return 0;
}
