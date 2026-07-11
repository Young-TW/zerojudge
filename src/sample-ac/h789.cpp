#include <iostream>
#include <vector>

using namespace std;

inline int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<int> a(N);
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
        }
        
        vector<int> pair_cnt(1000001, 0);
        long long ans = 0;
        
        for (int k = 0; k < N; ++k) {
            int ak = a[k];
            
            for (int g = 1; g * g <= ak; ++g) {
                if (ak % g == 0) {
                    ans += pair_cnt[g];
                    if (g * g != ak) {
                        ans += pair_cnt[ak / g];
                    }
                }
            }
            
            for (int i = 0; i < k; ++i) {
                int g = gcd(a[i], ak);
                pair_cnt[g]++;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
