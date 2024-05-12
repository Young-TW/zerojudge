#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    cout << (n / 6 == 1) * 590 + (n / 6 == 2) * 790 +
                (n / 6 >= 3 && n / 6 <= 9) * 890 + (n / 6 >= 10) * 399;
    return 0;
}