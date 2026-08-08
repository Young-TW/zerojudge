#include <bits/stdc++.h>
using namespace std;

/*
   q395 旗鼓相當 (Peers)

   兩隊各 N 名選手 (N 為奇數)，比賽時把兩隊選手一對一配對 (任意雙射)，
   每場 BP 值大者勝 (跨隊不會相同，故無平手)，勝場超過一半者贏得團體賽。

   對所有可能的配對而言：
     - 若 A 隊必勝 (在任何配對下 A 勝場都 > N/2) → 輸出 A
     - 若 B 隊必勝 → 輸出 B
     - 否則 (勝負會隨配對改變) → 輸出 X (旗鼓相當)

   令 maxWins(X,Y) = 在某個雙射下 X 隊能贏 Y 隊的最多場數 (貪心兩指針)。
   A 隊在所有配對下最少勝場 = N - maxWins(B,A)。
   A 必勝  <=>  N - maxWins(B,A) >= (N+1)/2  <=>  maxWins(B,A) <= (N-1)/2
   B 必勝  <=>  maxWins(A,B) <= (N-1)/2
*/

int maxWins(vector<long long> atk, vector<long long> def) {
    sort(atk.begin(), atk.end());
    sort(def.begin(), def.end());
    int j = 0, cnt = 0, n = (int)def.size();
    for (long long a : atk) {
        if (j < n && a > def[j]) { ++cnt; ++j; }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N;
    while (cin >> N) {
        vector<long long> A(N), B(N);
        for (long long i = 0; i < N; ++i) cin >> A[i];
        for (long long i = 0; i < N; ++i) cin >> B[i];

        int maxA = maxWins(A, B);   // A 能贏 B 的最多場數
        int maxB = maxWins(B, A);   // B 能贏 A 的最多場數
        long long half = (N - 1) / 2;

        if (maxB <= half)      cout << "A\n";
        else if (maxA <= half) cout << "B\n";
        else                   cout << "X\n";
    }
    return 0;
}
