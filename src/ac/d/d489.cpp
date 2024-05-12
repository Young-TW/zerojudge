#include <iostream>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    cout << ((a + b + c) / 2) * ((a + b + c) / 2 - a) * ((a + b + c) / 2 - b) *
                ((a + b + c) / 2 - c);
    return 0;
}