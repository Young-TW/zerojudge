#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

short dp2[3505];
short dp3[3505][3505];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        if (n == 2) {
            string A, B;
            cin >> A >> B;
            int LA = A.length();
            int LB = B.length();
            
            if (LA < LB) {
                swap(A, B);
                swap(LA, LB);
            }
            
            memset(dp2, 0, sizeof(dp2));
            int max_len = 0;
            
            for (int i = 1; i <= LA; ++i) {
                char ai = A[i-1];
                for (int j = LB; j >= 1; --j) {
                    if (ai == B[j-1]) {
                        dp2[j] = dp2[j-1] + 1;
                        if (dp2[j] > max_len) max_len = dp2[j];
                    } else {
                        dp2[j] = 0;
                    }
                }
            }
            cout << max_len << "\n";
        } else if (n == 3) {
            string A, B, C;
            cin >> A >> B >> C;
            int LA = A.length();
            int LB = B.length();
            int LC = C.length();
            
            if (LA < LB) { swap(A, B); swap(LA, LB); }
            if (LB < LC) { swap(B, C); swap(LB, LC); }
            if (LA < LB) { swap(A, B); swap(LA, LB); }
            
            memset(dp3, 0, sizeof(dp3));
            int max_len = 0;
            
            for (int i = 1; i <= LA; ++i) {
                char ai = A[i-1];
                for (int j = LB; j >= 1; --j) {
                    if (ai == B[j-1]) {
                        for (int k = LC; k >= 1; --k) {
                            if (ai == C[k-1]) {
                                dp3[j][k] = dp3[j-1][k-1] + 1;
                                if (dp3[j][k] > max_len) max_len = dp3[j][k];
                            } else {
                                dp3[j][k] = 0;
                            }
                        }
                    } else {
                        memset(dp3[j], 0, sizeof(short) * (LC + 1));
                    }
                }
            }
            cout << max_len << "\n";
        }
    }
    return 0;
}
