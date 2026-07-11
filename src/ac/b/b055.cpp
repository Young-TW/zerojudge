#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// 檢查兩個數字的位數組合是否與乘積的位數組合相同
bool isVampire(int x, int y, long long product) {
    // 如果兩者都以 0 結尾，則不符合定義
    if (x % 10 == 0 && y % 10 == 0) return false;

    char sProd[20];
    char sX[10];
    char sY[10];
    
    sprintf(sProd, "%lld", product);
    sprintf(sX, "%d", x);
    sprintf(sY, "%d", y);

    int lenProd = strlen(sProd);
    int lenX = strlen(sX);
    int lenY = strlen(sY);

    // 長度檢查：乘積長度應等於 x 長度 + y 長度
    if (lenProd != lenX + lenY) return false;

    int countProd[10] = {0};
    int countXY[10] = {0};

    for (int i = 0; i < lenProd; ++i) {
        countProd[sProd[i] - '0']++;
    }
    for (int i = 0; i < lenX; ++i) {
        countXY[sX[i] - '0']++;
    }
    for (int i = 0; i < lenY; ++i) {
        countXY[sY[i] - '0']++;
    }

    for (int i = 0; i < 10; ++i) {
        if (countProd[i] != countXY[i]) return false;
    }

    return true;
}

void solve(int n) {
    if (n % 2 != 0) return; // 題目定義需為偶數個位數，雖然輸入可能只問偶數位
    
    long long start = 1;
    for (int i = 1; i < n; ++i) start *= 10;
    
    long long end = start * 10;
    
    int halfLen = n / 2;
    long long minFang = 1;
    for (int i = 1; i < halfLen; ++i) minFang *= 10;
    
    long long maxFang = minFang * 10 - 1;

    vector<long long> results;

    // 遍歷所有可能的 fang 組合
    // 為了避免重複 (a*b 和 b*a)，讓第二個循環從 i 開始
    for (long long i = minFang; i <= maxFang; ++i) {
        // 優化：如果 i * minFang 已經超過 n 位數的上限，可以提前結束內層？
        // 不，因為 j 會變大，乘積也會變大。
        // 如果 i * i 已經超過 end，那後面的都不用算了
        if (i * i >= end) break;

        for (long long j = i; j <= maxFang; ++j) {
            long long prod = i * j;
            
            if (prod >= end) break; // 超過 n 位數，後續 j 更大，直接跳出內層
            if (prod < start) continue; // 還不到 n 位數

            // 題目要求輸出偶數的 Vampire Number
            if (prod % 2 != 0) continue;

            if (isVampire((int)i, (int)j, prod)) {
                results.push_back(prod);
            }
        }
    }

    sort(results.begin(), results.end());
    
    // 去除重複
    if (!results.empty()) {
        cout << results[0] << "\n";
        for (size_t k = 1; k < results.size(); ++k) {
            if (results[k] != results[k-1]) {
                cout << results[k] << "\n";
            }
        }
    }
}

int main() {
    // 加速 I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        solve(n);
    }

    return 0;
}
