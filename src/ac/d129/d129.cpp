// d129 - 00136 Ugly Numbers (UVa 136)
// Self-written. Compute the 1500th ugly number (prime factors only 2,3,5; 1 counts).
// Standard three-pointer merge DP: each new ugly number = a previous ugly * {2,3,5}.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    const int n = 1500;
    vector<long long> ugly(n);
    ugly[0] = 1;

    int i2 = 0, i3 = 0, i5 = 0;
    for (int i = 1; i < n; ++i) {
        long long n2 = ugly[i2] * 2, n3 = ugly[i3] * 3, n5 = ugly[i5] * 5;
        long long m = min(n2, min(n3, n5));
        ugly[i] = m;
        if (m == n2) i2++;
        if (m == n3) i3++;
        if (m == n5) i5++;
    }

    cout << "The 1500'th ugly number is " << ugly[n - 1] << ".\n";
    return 0;
}
