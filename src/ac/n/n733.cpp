#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1000005;
int X[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        for (int t = 1; t <= T; ++t) {
            int N, M, K;
            cin >> N >> M >> K;
            
            int cnt[105];
            memset(cnt, 0, sizeof(cnt));
            int distinct = 0;
            int min_len = N + 1;
            int left = 1;
            
            for (int right = 1; right <= N; ++right) {
                if (right == 1) {
                    X[right] = 1;
                } else if (right == 2) {
                    X[right] = 2;
                } else if (right == 3) {
                    X[right] = 3;
                } else {
                    X[right] = (X[right-1] + X[right-2] + X[right-3]) % M + 1;
                }
                
                if (X[right] >= 1 && X[right] <= K) {
                    if (cnt[X[right]] == 0) {
                        distinct++;
                    }
                    cnt[X[right]]++;
                }
                
                while (distinct == K) {
                    if (right - left + 1 < min_len) {
                        min_len = right - left + 1;
                    }
                    if (X[left] >= 1 && X[left] <= K) {
                        cnt[X[left]]--;
                        if (cnt[X[left]] == 0) {
                            distinct--;
                        }
                    }
                    left++;
                }
            }
            
            cout << "Case " << t << ": ";
            if (min_len == N + 1) {
                cout << "sequence nai\n";
            } else {
                cout << min_len << "\n";
            }
        }
    }
    
    return 0;
}
