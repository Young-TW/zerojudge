#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

const int BASE = 1000000000;

void add(vector<int>& a, const vector<int>& b) {
    int carry = 0;
    for (size_t i = 0; i < max(a.size(), b.size()) || carry; ++i) {
        if (i >= a.size()) a.push_back(0);
        long long sum = (long long)a[i] + carry;
        if (i < b.size()) sum += b[i];
        a[i] = sum % BASE;
        carry = sum / BASE;
    }
}

void print(const vector<int>& v) {
    cout << v.back();
    for (size_t i = v.size() - 1; i-- > 0; ) {
        cout.width(9);
        cout.fill('0');
        cout << v[i];
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;
    while (cin >> m) {
        if (m <= 1) {
            cout << "0\n";
        } else if (m == 2) {
            cout << "1\n";
        } else {
            vector<int> f[3];
            f[1] = {0};
            f[2] = {1};
            for (int i = 3; i <= m; ++i) {
                f[i % 3].swap(f[(i - 2) % 3]);
                add(f[i % 3], f[(i - 1) % 3]);
            }
            print(f[m % 3]);
        }
    }
    return 0;
}
