#include <iostream>
using namespace std;

int main() {
    long long n, m;
    int k;
    while (cin >> n >> m >> k) {
        int cost[2] = {32, 55};
        int cur = k;
        long long t = 0;
        bool ate = false;
        while (n >= cost[cur]) {
            ate = true;
            n -= cost[cur];
            cout << t << ": Wayne ";
            if (cur == 0) cout << "eats an Apple pie, and now he ";
            else cout << "drinks a Corn soup, and now he ";
            if (n == 0) cout << "doesn't have money.\n";
            else if (n == 1) cout << "has 1 dollar.\n";
            else cout << "has " << n << " dollars.\n";
            cur = 1 - cur;
            t += m;
        }
        if (!ate) cout << "Wayne can't eat and drink.\n";
    }
    return 0;
}
