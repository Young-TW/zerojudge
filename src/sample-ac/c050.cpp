#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAX_N = 1000000;
    vector<bool> is_prime(MAX_N, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i < MAX_N; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j < MAX_N; j += i) {
                is_prime[j] = false;
            }
        }
    }

    int n;
    while (cin >> n && n != 0) {
        bool found = false;
        for (int a = 3; a <= n / 2; a += 2) {
            if (is_prime[a] && is_prime[n - a]) {
                cout << n << " = " << a << " + " << n - a << "\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Goldbach's conjecture is wrong.\n";
        }
    }

    return 0;
}
