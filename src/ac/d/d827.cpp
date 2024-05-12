#include <iostream>
using namespace std;

int main() {
    int n, m = 0;
    cin >> n;
    m += 5 * (n % 12);
    m += 50 * (n / 12);
    cout << m << endl;
    return 0;
}