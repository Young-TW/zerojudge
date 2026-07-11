#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int find_cycle_length(int m) {
    if (m == 1) return 1;
    vector<int> fib_mod = {1, 1};
    int a = 1, b = 1;
    int cycle_length = 0;
    for (int i = 2; ; ++i) {
        int c = (a + b) % m;
        a = b;
        b = c;
        if (a == 1 && b == 1) {
            cycle_length = i - 1;
            break;
        }
    }
    return cycle_length;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int k = 1; k <= n; ++k) {
        cout << find_cycle_length(k) << '\n';
    }
    return 0;
}
