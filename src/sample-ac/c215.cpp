#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

ull reverse_bits(ull x) {
    ull res = 0;
    int bits = 0;
    ull temp = x;
    while (temp > 0) {
        temp >>= 1;
        bits++;
    }
    for (int i = 0; i < bits; i++) {
        if (x & (1ULL << i)) {
            res |= (1ULL << (bits - 1 - i));
        }
    }
    return res;
}

int count_ones(ull x) {
    int cnt = 0;
    while (x > 0) {
        cnt += (x & 1);
        x >>= 1;
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ull n;
    while (cin >> n) {
        ull total = 0;
        for (ull i = 1; i <= n; i++) {
            ull rev = reverse_bits(i);
            ull sum = i + rev;
            total += count_ones(sum);
        }
        cout << total << '\n';
    }
    return 0;
}
