#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // 題目要求 N 為 4 位數，介於 1000 到 9999 之間
    for (int N = 1000; N <= 9999; ++N) {
        // 1 + sqrt(N+1) 必須是整數，所以 N+1 必須是完全平方數
        int k_plus_1 = -1;
        for (int i = 32; i <= 100; ++i) {
            if (i * i == N + 1) {
                k_plus_1 = i;
                break;
            }
        }
        
        if (k_plus_1 != -1) {
            // 找出 N 所有的因數並由小到大排序
            vector<int> divisors;
            for (int i = 1; i * i <= N; ++i) {
                if (N % i == 0) {
                    divisors.push_back(i);
                    if (i * i != N) {
                        divisors.push_back(N / i);
                    }
                }
            }
            sort(divisors.begin(), divisors.end());
            
            // 目標為 1 + sqrt(N+1);k_plus_1 存的是 sqrt(N+1)=i,故須 +1(修正 off-by-one)
            if (divisors.size() >= 4 && divisors[3] == k_plus_1 + 1) {
                cout << N << '\n';
                break; // 輸出符合條件的最小 N 即可
            }
        }
    }
    return 0;
}
