#include <iostream>
using namespace std;

int main() {
    long long a, b;
    while (cin >> a >> b) {
        if (a <= 0 || b >= a) {
            cout << "能\n";
        } else {
            cout << "不能\n";
        }
    }
    return 0;
}
