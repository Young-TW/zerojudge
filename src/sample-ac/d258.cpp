#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        int episodes = 0;
        bool possible = true;
        while (n > 1) {
            if (n < m) {
                possible = false;
                break;
            }
            int games = n / m;
            int seeds = n % m;
            episodes += games;
            n = games + seeds;
        }
        if (possible && n == 1) {
            cout << episodes << "\n";
        } else {
            cout << "cannot do this\n";
        }
    }
    return 0;
}
