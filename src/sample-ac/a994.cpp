#include <iostream>
#include <vector>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long N;
    int M;
    while (cin >> N >> M) {
        vector<long long> arr(M);
        for (int i = 0; i < M; ++i) {
            cin >> arr[i];
        }
        
        long long ans = N;
        for (int mask = 1; mask < (1 << M); ++mask) {
            int cnt = 0;
            long long lcm = 1;
            for (int i = 0; i < M; ++i) {
                if (mask & (1 << i)) {
                    cnt++;
                    long long g = gcd(lcm, arr[i]);
                    lcm = lcm / g * arr[i];
                    if (lcm > N) {
                        lcm = 0;
                        break;
                    }
                }
            }
            if (lcm > 0) {
                if (cnt % 2 == 1) {
                    ans -= N / lcm;
                } else {
                    ans += N / lcm;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
