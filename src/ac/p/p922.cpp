#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        long long total1 = 0, total2 = 0;
        for (int i = 0; i < n; i++) {
            long long a, b, c;
            cin >> a >> b >> c;
            if (a > b) total1 += c;
            else total2 += c;
        }
        if (total1 >= total2) cout << "1 " << total1 << "\n";
        else cout << "2 " << total2 << "\n";
    }
    return 0;
}
