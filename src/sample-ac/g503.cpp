#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    long long C;
    int M;
    while (cin >> N >> C >> M) {
        long long MOD = 1;
        for (int i = 0; i < M; ++i) {
            MOD *= 10;
        }
        
        C %= MOD;
        
        vector<long long> coeff(101, 0);
        int max_B = 0;
        
        for (int i = 0; i < N; ++i) {
            long long A;
            int B;
            cin >> A >> B;
            A %= MOD;
            coeff[B] = (coeff[B] + A) % MOD;
            if (B > max_B) {
                max_B = B;
            }
        }
        
        long long ans = 0;
        for (int i = max_B; i >= 0; --i) {
            ans = (ans * C + coeff[i]) % MOD;
        }
        
        long long final_ans = (ans < 0 ? -ans : ans) % MOD;
        cout << setw(M) << setfill('0') << final_ans << "\n";
    }
    
    return 0;
}
