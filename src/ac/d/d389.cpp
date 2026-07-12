#include <iostream>
using namespace std;

int main() {
    long long ans[77];
    ans[1] = 1;
    ans[2] = 2;
    ans[3] = 2;
    for (int i = 4; i <= 76; i++) {
        ans[i] = ans[i-2] + ans[i-3];
    }
    int n;
    while (cin >> n) {
        cout << ans[n] << endl;
    }
    return 0;
}
