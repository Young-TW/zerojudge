#include <iostream>

using namespace std;

long long count_ones(long long n) {
    if (n < 0) return 0;
    long long res = 0;
    for (int i = 0; i < 31; ++i) {
        long long high = n >> (i + 1);
        long long low = n & ((1LL << i) - 1);
        if (n & (1LL << i)) {
            res += high * (1LL << i) + low + 1;
        } else {
            res += high * (1LL << i);
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long a, b;
    int case_num = 1;
    
    while (cin >> a >> b) {
        if (a == 0 && b == 0) break;
        long long ans = count_ones(b) - count_ones(a - 1);
        cout << "Case " << case_num << ": " << ans << "\n";
        case_num++;
    }
    
    return 0;
}
