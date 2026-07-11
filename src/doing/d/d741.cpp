#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

// 計算質因數分解，並返回最少次數與方法數
// 對於數字 n，我們將其分解為質因數 p1^a1 * p2^a2 * ... * pk^ak
// 最少次數 = sum(ai * pi) 對於所有 i
// 方法數 = (sum(ai))! / (a1! * a2! * ... * ak!) 對於所有 i
// 但實際上，這裡的「方法數」是指將質因數排列的組合數
// 因為每次操作可以是複製任何現有的倍數，所以順序很重要
// 實際上這題的邏輯是：
// 要得到 n 顆星星，我們需要將 n 分解為質因數
// 每個質因數 p 需要 p 次操作 (1 次 Copy, p-1 次 Paste)
// 總操作次數 = 所有質因數的和 (重複計算)
// 方法數 = 這些質因數的排列組合數

long long factorial(int n) {
    if (n <= 1) return 1;
    long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

void solve() {
    long long n;
    while (cin >> n) {
        if (n == 1) {
            cout << "min : 0" << endl;
            cout << "way : 1" << endl;
            continue;
        }

        // 質因數分解
        vector<long long> factors;
        long long temp = n;
        
        // 處理 2
        while (temp % 2 == 0) {
            factors.push_back(2);
            temp /= 2;
        }
        
        // 處理奇數質因數
        for (long long i = 3; i * i <= temp; i += 2) {
            while (temp % i == 0) {
                factors.push_back(i);
                temp /= i;
            }
        }
        
        // 如果 temp > 1，則 temp 本身是質數
        if (temp > 1) {
            factors.push_back(temp);
        }

        // 計算最少次數：所有質因數的和
        long long min_ops = 0;
        for (long long f : factors) {
            min_ops += f;
        }

        // 計算方法數：多重集合的排列數
        // 公式：n! / (n1! * n2! * ... * nk!)
        // 其中 n 是總因數個數，ni 是每個不同因數的重複次數
        
        map<long long, int> count_map;
        for (long long f : factors) {
            count_map[f]++;
        }
        
        long long total_factors = factors.size();
        long long denominator = 1;
        
        for (auto& pair : count_map) {
            denominator *= factorial(pair.second);
        }
        
        long long ways = factorial(total_factors) / denominator;

        cout << "min : " << min_ops << endl;
        cout << "way : " << ways << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
