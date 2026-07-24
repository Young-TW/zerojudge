#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    // 優化 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long N, M;
    // 使用 while 迴圈處理多筆測資直到 EOF
    while (cin >> N >> M) {
        vector<long long> ingredients(N);
        long long K;

        // 讀入 N 個食材數量
        for (int i = 0; i < N; ++i) {
            cin >> ingredients[i];
        }
        // 讀入最後一個數字 K (原始份數或基準)
        cin >> K;

        // 處理每個食材
        for (int i = 0; i < N; ++i) {
            // 計算公式：ceil(ingredients[i] * K / M)
            // 為了避免浮點數誤差，使用整數運算：(numerator + denominator - 1) / denominator
            // 由於 ingredients[i] * K 可能超過 long long 範圍，使用 __int128
            
            __int128 num = (__int128)ingredients[i] * K;
            __int128 den = (__int128)M;
            
            // 計算 ceil(num / den)
            __int128 result = (num + den - 1) / den;
            
            // 輸出結果
            if (i > 0) cout << " ";
            cout << (long long)result;
        }
        cout << "\n";
    }

    return 0;
}
