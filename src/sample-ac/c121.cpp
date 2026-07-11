#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> add(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    int carry = 0;
    size_t max_len = max(a.size(), b.size());
    for (size_t i = 0; i < max_len || carry; ++i) {
        int sum = carry;
        if (i < a.size()) sum += a[i];
        if (i < b.size()) sum += b[i];
        carry = sum / 10;
        res.push_back(sum % 10);
    }
    return res;
}

string vecToStr(const vector<int>& v) {
    string s;
    for (int i = v.size() - 1; i >= 0; --i) {
        s += (v[i] + '0');
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<vector<int>> fibs(5001);
    fibs[0] = {0};
    fibs[1] = {1};
    for (int i = 2; i <= 5000; ++i) {
        fibs[i] = add(fibs[i-1], fibs[i-2]);
    }
    
    int n;
    while (cin >> n) {
        cout << "The Fibonacci number for " << n << " is " << vecToStr(fibs[n]) << "\n";
    }
    
    return 0;
}
