#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long T;
    // 雖然題目說每個測資點只有一組測資，但使用 while 迴圈讀取到 EOF 更穩健
    while (cin >> N >> T) {
        vector<vector<long long>> spells(4, vector<long long>(N));
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> spells[i][j];
            }
        }

        // 第一行是公會長（你）的魔法強度
        sort(spells[0].begin(), spells[0].end());

        // 預先計算第三、四位成員（精英）的所有魔法強度之和
        vector<long long> cd_sums;
        cd_sums.reserve(static_cast<size_t>(N) * N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cd_sums.push_back(spells[2][i] + spells[3][j]);
            }
        }
        sort(cd_sums.begin(), cd_sums.end());

        bool found = false;
        long long ans = 0;

        // 從公會長最小的魔法強度開始嘗試，找到第一個可行解即為最小魔力消耗
        for (long long a : spells[0]) {
            if (a > T) break; // 魔法強度均為正整數，若 a > T 則總和必超過 T
            long long target3 = T - a; // 副會長 + 兩精英 需達到的總傷害

            for (long long b : spells[1]) {
                if (b > target3) continue; // 同理，b 不能超過剩餘需求
                long long need = target3 - b; // 兩精英需達到的傷害
                if (binary_search(cd_sums.begin(), cd_sums.end(), need)) {
                    ans = a * a; // 魔力消耗為公會長魔法強度的平方
                    found = true;
                    break;
                }
            }
            if (found) break;
        }

        if (found) {
            cout << ans << '\n';
        } else {
            cout << "Gein Suan !!!\n";
        }
    }
    return 0;
}
