#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    while (cin >> t) {
        while (t--) {
            int n;
            unsigned long long k;
            cin >> n >> k;
            
            unsigned long long limit = 1;
            for(int i = 0; i < n; ++i) limit *= 10;
            
            auto next_val = [limit](unsigned long long x) {
                unsigned long long sq = x * x;
                while (sq >= limit) {
                    sq /= 10;
                }
                return sq;
            };
            
            unsigned long long max_val = k;
            unsigned long long tortoise = next_val(k);
            unsigned long long hare = next_val(next_val(k));
            while (tortoise != hare) {
                tortoise = next_val(tortoise);
                hare = next_val(next_val(hare));
            }
            
            tortoise = k;
            while (tortoise != hare) {
                if (tortoise > max_val) max_val = tortoise;
                tortoise = next_val(tortoise);
                hare = next_val(hare);
            }
            
            do {
                if (tortoise > max_val) max_val = tortoise;
                tortoise = next_val(tortoise);
            } while (tortoise != hare);
            
            cout << max_val << "\n";
        }
    }
    return 0;
}
