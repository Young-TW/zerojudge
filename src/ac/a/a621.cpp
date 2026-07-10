#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long v = 1;
    for (int i = 0; i <= n; i++) {
        cout << "2^" << i << " = " << v << "\n";
        v *= 2;
    }
    return 0;
}
