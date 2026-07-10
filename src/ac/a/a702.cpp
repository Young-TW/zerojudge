#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int LIMIT = 20000005;

static bool is_comp[LIMIT];

int main() {
    // Sieve of Eratosthenes
    memset(is_comp, 0, sizeof(is_comp));
    is_comp[0] = is_comp[1] = true;
    for (long long i = 2; i * i < LIMIT; ++i) {
        if (!is_comp[i]) {
            for (long long j = i * i; j < LIMIT; j += i) {
                is_comp[j] = true;
            }
        }
    }

    // Collect cousin primes (p, p+4) both prime
    vector<pair<int, int>> cousins;
    cousins.reserve(200000);
    for (int p = 3; p + 4 < LIMIT; ++p) {
        if (!is_comp[p] && !is_comp[p + 4]) {
            cousins.push_back(make_pair(p, p + 4));
        }
    }

    int s;
    while (scanf("%d", &s) == 1) {
        if (s < 1 || s > (int)cousins.size()) continue;
        printf("(%d, %d)\n", cousins[s - 1].first, cousins[s - 1].second);
    }
    return 0;
}
