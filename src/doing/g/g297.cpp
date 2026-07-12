#include <iostream>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    while (b) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

long long count_pours(int fromCap, int toCap, int target) {
    long long pours = 0;
    int from = fromCap;
    int to = 0;
    while (true) {
        if (from == target || to == target) {
            return pours;
        }
        if (to == 0) {
            if (from >= toCap) {
                if (target == toCap) {
                    return pours + 1;
                }
                if (target < from && (from - target) % toCap == 0) {
                    long long i = (from - target) / toCap;
                    if (i >= 1 && i <= from / toCap) {
                        return pours + i;
                    }
                }
                long long q = from / toCap;
                pours += q;
                from = from % toCap;
                if (from == 0) {
                    from = fromCap;
                }
            } else {
                pours++;
                to = from;
                from = 0;
                if (from == target || to == target) {
                    return pours;
                }
                from = fromCap;
            }
        } else {
            int transfer = min(from, toCap - to);
            to += transfer;
            from -= transfer;
            pours++;
            if (from == target || to == target) {
                return pours;
            }
            if (to == toCap) {
                to = 0;
            }
            if (from == 0) {
                from = fromCap;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int P;
    if (!(cin >> P)) return 0;
    while (P--) {
        int n, m, k;
        cin >> n >> m >> k;
        if (k > max(n, m)) {
            cout << "老師請不要鬧!\n";
            continue;
        }
        if (k == 0) {
            cout << 0 << '\n';
            continue;
        }
        int g = gcd(n, m);
        if (k % g != 0) {
            cout << "老師請不要鬧!\n";
            continue;
        }
        long long ans1 = count_pours(n, m, k);
        long long ans2 = count_pours(m, n, k);
        long long ans = min(ans1, ans2);
        cout << ans << '\n';
    }
    return 0;
}
