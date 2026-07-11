#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> multiply(const vector<int>& num, int x) {
    vector<int> result;
    int carry = 0;
    for (int digit : num) {
        long long product = digit * 1LL * x + carry;
        result.push_back(product % 10);
        carry = product / 10;
    }
    while (carry > 0) {
        result.push_back(carry % 10);
        carry /= 10;
    }
    return result;
}

vector<int> power(int n, int m) {
    if (m == 0) return {1};
    vector<int> result = {1};
    for (int i = 0; i < m; ++i) {
        result = multiply(result, n);
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        if (n == 1) {
            cout << "1\n";
            continue;
        }
        vector<int> res = power(n, m);
        for (auto it = res.rbegin(); it != res.rend(); ++it) {
            cout << *it;
        }
        cout << '\n';
    }
    return 0;
}
