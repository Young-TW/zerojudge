#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;

/*
   f430  高雄市109 第九題：開票策略

   N 袋選票，第 i 袋有 X_i 票投給候選人 X、Y_i 票投給候選人 Y
   (每袋至少一張有效票，tot_i = X_i+Y_i >= 1)。
   必須恰好開 M 袋 (其餘銷毀)。

   第一列：讓 X 的總得票率 (ΣX)/(Σtot) 最大 → 輸出最大值
   第二列：讓 Y 的總得票率 (ΣY)/(Σtot) 最大 → 輸出最大值

   在「恰選 M 個」的均勻擬陣上做線性分式最大化，使用 Dinkelbach：
     給定目前比值 P/Q，令 V_i = num_i*Q - P*tot_i，
     取 V_i 最大的 M 個為新集合，若新比值嚴格較大則更新，直到收斂。
   全程整數運算，最後化為最簡分數。

   輸出：比值必落在 [0,1]。若為 0 或 1 輸出整數，否則輸出 0<a<b 的最簡分數 a/b。
*/

int N, M;
vector<ll> Xv, Yv, tot;

// 最大化 (Σ num)/(Σ tot)，回傳最簡表示 (P,Q)
pair<ll,ll> maximizeRatio(const vector<ll>& num) {
    vector<int> id(N);
    iota(id.begin(), id.end(), 0);

    // 初始：以 num 值取最大的 M 個 (相當於 λ=0)
    nth_element(id.begin(), id.begin() + (M - 1), id.end(),
                [&](int a, int b){ return num[a] > num[b]; });
    ll P = 0, Q = 0;
    for (int t = 0; t < M; ++t) { P += num[id[t]]; Q += tot[id[t]]; }

    vector<ll> V(N);
    for (int iter = 0; iter < 1000; ++iter) {
        for (int i = 0; i < N; ++i) V[i] = num[i] * Q - P * tot[i];
        iota(id.begin(), id.end(), 0);
        nth_element(id.begin(), id.begin() + (M - 1), id.end(),
                    [&](int a, int b){ return V[a] > V[b]; });
        ll nP = 0, nQ = 0;
        for (int t = 0; t < M; ++t) { nP += num[id[t]]; nQ += tot[id[t]]; }
        // 若新比值嚴格較大 (nP/nQ > P/Q  <=>  nP*Q > P*nQ) 則更新
        if ((lll)nP * Q > (lll)P * nQ) { P = nP; Q = nQ; }
        else break;
    }

    ll g = __gcd(P, Q);
    if (g == 0) g = 1;
    return {P / g, Q / g};
}

void printRatio(pair<ll,ll> r) {
    ll P = r.first, Q = r.second;
    if (P == 0)        cout << "0\n";
    else if (P == Q)   cout << "1\n";
    else               cout << P << '/' << Q << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> N >> M) {
        Xv.assign(N, 0); Yv.assign(N, 0); tot.assign(N, 0);
        for (int i = 0; i < N; ++i) {
            cin >> Xv[i] >> Yv[i];
            tot[i] = Xv[i] + Yv[i];
        }
        printRatio(maximizeRatio(Xv));
        printRatio(maximizeRatio(Yv));
    }
    return 0;
}
