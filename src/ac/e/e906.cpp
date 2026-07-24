#include <iostream>

using namespace std;

int main() {
    // 優化 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    // 先讀入測試資料的筆數
    if (cin >> t) {
        // 根據筆數循環讀取每一筆測資
        while (t--) {
            long long n;
            cin >> n;
            // 根據範例規律，輸出為 n + 1
            cout << (n + 1) << "\n";
        }
    }

    return 0;
}
