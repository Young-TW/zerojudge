#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string gcdBinaryStrings(const string &a, const string &b) {
    if (a == "0") return b;
    if (b == "0") return a;

    string x = a, y = b;
    int shift = 0;

    while (x != y) {
        bool xEven = (x.back() == '0');
        bool yEven = (y.back() == '0');

        if (xEven && yEven) {
            x.pop_back();
            y.pop_back();
            shift++;
        } else if (xEven) {
            x.pop_back();
        } else if (yEven) {
            y.pop_back();
        } else {
            if (x.size() > y.size() || (x.size() == y.size() && x > y)) {
                swap(x, y);
            }
            string temp = y;
            int borrow = 0;
            for (int i = x.size() - 1, j = y.size() - 1; i >= 0; --i, --j) {
                int xd = x[i] - '0';
                int yd = y[j] - '0';
                int diff = yd - xd - borrow;
                if (diff < 0) {
                    diff += 2;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                temp[j] = diff + '0';
            }
            for (int j = y.size() - x.size() - 1; j >= 0 && borrow; --j) {
                int yd = y[j] - '0';
                int diff = yd - borrow;
                if (diff < 0) {
                    diff += 2;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                temp[j] = diff + '0';
            }
            while (temp.size() > 1 && temp[0] == '0') {
                temp.erase(temp.begin());
            }
            y = temp;
        }
    }

    for (int i = 0; i < shift; ++i) {
        x.push_back('0');
    }
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    while (cin >> a >> b) {
        string result = gcdBinaryStrings(a, b);
        cout << result << '\n';
    }

    return 0;
}
