#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N;
    if (!(cin >> N)) return 0;          // no input
    vector<long long> A(N), B(N);
    for (long long i = 0; i < N; ++i) cin >> A[i];
    for (long long i = 0; i < N; ++i) cin >> B[i];
    long long X, Y;
    cin >> X >> Y;

    long long sumA = 0, sumB = 0;
    long long answer = -1;
    for (long long i = 0; i < N; ++i) {
        sumA += A[i];
        sumB += B[i];
        if (sumA >= X && sumB >= Y) {
            answer = i + 2;   // i is 0‑based, need (i+1)+1 as required
            break;
        }
    }

    cout << answer << "\n";
    return 0;
}
