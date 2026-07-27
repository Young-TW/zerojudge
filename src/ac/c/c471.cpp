#include <bits/stdc++.h>
using namespace std;

struct Item {
    long long w;   // weight
    long long f;   // frequency
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        vector<Item> a(N);
        for (int i = 0; i < N; ++i) cin >> a[i].w;
        for (int i = 0; i < N; ++i) cin >> a[i].f;

        sort(a.begin(), a.end(),
            [](const Item& A, const Item& B) {
                // A before B  <=>  wA / fA <= wB / fB
                // avoid division: compare wA * fB and wB * fA
                return A.w * B.f < B.w * A.f;
            });

        long long cumW = 0;
        long long ans  = 0;
        for (const auto& it : a) {
            ans  += cumW * it.f;
            cumW += it.w;
        }
        cout << ans << '\n';
    }
    return 0;
}
