#include <iostream>
using namespace std;

int main(){
    long long a, b, c, p, q;
    while (cin >> a >> b >> c >> p >> q) {
        long long ans = (p * b + q * c) / (2 * a);
        cout << ans << endl;
    }
    return 0;
}
