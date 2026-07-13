#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

int main() {
    int b;
    string N;
    while (cin >> b >> N) {
        int d = N.size();
        long long sum = 0;
        long long num = 0;

        for (char c : N) {
            int digit;
            if (c >= '0' && c <= '9') {
                digit = c - '0';
            } else {
                digit = c - 'A' + 10;
            }
            num = num * b + digit;
        }

        for (char c : N) {
            int digit;
            if (c >= '0' && c <= '9') {
                digit = c - '0';
            } else {
                digit = c - 'A' + 10;
            }
            long long power = 1;
            for (int i = 0; i < d; ++i) {
                power *= digit;
            }
            sum += power;
        }

        if (sum == num) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
