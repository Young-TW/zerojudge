#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    // 1/17 = 0.0588235294117647... (repeating block of length 16)
    const string block = "0588235294117647";
    const int L = 16;
    long long blockSum = 0;
    vector<long long> prefix(L + 1, 0);
    for (int i = 0; i < L; i++) {
        blockSum += block[i] - '0';
        prefix[i + 1] = prefix[i] + (block[i] - '0');
    }

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        long long n;
        cin >> n;
        long long full = n / L;
        int rem = (int)(n % L);
        long long digit = block[(n - 1) % L] - '0';
        long long sum = full * blockSum + prefix[rem];
        cout << digit << ' ' << sum << '\n';
    }
    return 0;
}
