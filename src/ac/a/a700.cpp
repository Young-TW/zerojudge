#include <iostream>
using namespace std;

int main() {
    int i, j;
    while (cin >> i >> j) {
        unsigned long long exp = (unsigned long long)(i - 1) * 8 + (j - 1);
        cout << (1ULL << exp) << endl;
    }
    return 0;
}
