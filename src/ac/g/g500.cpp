#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int cnt[2005] = {0};
    for (int n1 = 1; n1 <= 30; ++n1) {
        for (int n2 = n1 + 1; n2 <= 30; ++n2) {
            for (int n3 = n2 + 1; n3 <= 30; ++n3) {
                for (int n4 = n3 + 1; n4 <= 30; ++n4) {
                    for (int n5 = n4 + 1; n5 <= 30; ++n5) {
                        int sum = n1 * 20 + n2 * n2 + n3 * 3 + (n3 + n4) * 4 + (n5 - n4) * 5;
                        if (sum <= 2000) {
                            cnt[sum]++;
                        }
                    }
                }
            }
        }
    }
    
    int N;
    while (cin >> N) {
        if (N <= 2000 && cnt[N] > 0) {
            long long c = cnt[N];
            cout << c * c * c << "\n";
        } else {
            cout << N * 5 - 3 << "\n";
        }
    }
    
    return 0;
}
