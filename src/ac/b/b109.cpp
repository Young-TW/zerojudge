#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<int> s(n);
        for (int i = 0; i < n; ++i) {
            cin >> s[i];
        }
        
        vector<long long> num(n, -1);
        vector<long long> den(n, 1);
        
        long long max_finish_num = -1;
        long long max_finish_den = 1;
        long long ans_start = -1;
        int ans_machine = -1;

        long long T, Q;
        while (cin >> T >> Q) {
            if (T == 0 && Q == 0) break;
            
            long long best_num = -1;
            long long best_den = 1;
            long long best_start = -1;
            int best_machine = -1;
            int best_s = -1;

            for (int i = 0; i < n; ++i) {
                long long t_start;
                if (num[i] == -1) {
                    t_start = T + 5;
                } else {
                    long long ceil_finish = (num[i] + den[i] - 1) / den[i];
                    t_start = max(T, ceil_finish + 10) + 5;
                }
                long long new_num = t_start * s[i] + Q;
                long long new_den = s[i];
                
                bool better = false;
                if (best_num == -1) {
                    better = true;
                } else {
                    if (new_num * best_den < best_num * new_den) {
                        better = true;
                    } else if (new_num * best_den == best_num * new_den) {
                        if (s[i] > best_s) {
                            better = true;
                        }
                    }
                }
                
                if (better) {
                    best_num = new_num;
                    best_den = new_den;
                    best_start = t_start;
                    best_machine = i + 1;
                    best_s = s[i];
                }
            }
            
            num[best_machine - 1] = best_num;
            den[best_machine - 1] = best_den;
            
            if (best_num * max_finish_den > max_finish_num * best_den) {
                max_finish_num = best_num;
                max_finish_den = best_den;
                ans_start = best_start;
                ans_machine = best_machine;
            }
        }
        cout << ans_start << " " << ans_machine << "\n";
    }
    return 0;
}
