#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main() {
    vector<int> primes;
    for (int i = 2; i <= 100; ++i) {
        bool is_prime = true;
        for (int j = 2; j * j <= i; ++j) {
            if (i % j == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            primes.push_back(i);
        }
    }

    int n;
    while (cin >> n && n != 0) {
        printf("%3d! =", n);
        int cnt = 0;
        for (int i = 0; i < (int)primes.size() && primes[i] <= n; ++i) {
            int p = primes[i];
            int count = 0;
            int temp = n;
            while (temp >= p) {
                temp /= p;
                count += temp;
            }
            if (cnt % 15 == 0 && cnt > 0) {
                printf("\n      ");
            }
            printf("%3d", count);
            cnt++;
        }
        printf("\n");
    }

    return 0;
}
