#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        if (n < 0) {
            cout << "-1" << endl;
            break;
        }
        if (n == 0) {
            cout << "0" << endl;
            continue;
        }
        vector<int> digits;
        int num = n;
        while (num > 0) {
            digits.push_back(num % 8);
            num /= 8;
        }
        for (int i = digits.size() - 1; i >= 0; --i) {
            cout << digits[i];
        }
        cout << endl;
    }
    return 0;
}
