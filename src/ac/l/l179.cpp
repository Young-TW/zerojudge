#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 305;
int A[MAXN][MAXN];
int B[MAXN], S[MAXN];
long long P[MAXN + 1];
int L[MAXN], R[MAXN];
long long left_min_P[MAXN], right_max_P[MAXN];

struct Node {
    int idx;
    long long val;
};
Node stk[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    while (cin >> N >> M) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> A[i][j];
            }
        }

        long long ans = 0;

        for (int r1 = 0; r1 < N; ++r1) {
            for (int j = 0; j < M; ++j) {
                B[j] = A[r1][j];
                S[j] = A[r1][j];
            }

            for (int r2 = r1; r2 < N; ++r2) {
                if (r2 > r1) {
                    for (int j = 0; j < M; ++j) {
                        B[j] = min(B[j], A[r2][j]);
                        S[j] += A[r2][j];
                    }
                }

                P[0] = 0;
                for (int j = 0; j < M; ++j) {
                    P[j + 1] = P[j] + S[j];
                }

                int top = 0;
                for (int i = 0; i < M; ++i) {
                    long long min_P = P[i];
                    while (top > 0 && B[stk[top - 1].idx] >= B[i]) {
                        min_P = min(min_P, stk[top - 1].val);
                        top--;
                    }
                    L[i] = (top == 0) ? -1 : stk[top - 1].idx;
                    left_min_P[i] = min_P;
                    stk[top].idx = i;
                    stk[top].val = min_P;
                    top++;
                }

                top = 0;
                for (int i = M - 1; i >= 0; --i) {
                    long long max_P = P[i + 1];
                    while (top > 0 && B[stk[top - 1].idx] > B[i]) {
                        max_P = max(max_P, stk[top - 1].val);
                        top--;
                    }
                    R[i] = (top == 0) ? M : stk[top - 1].idx;
                    right_max_P[i] = max_P;
                    stk[top].idx = i;
                    stk[top].val = max_P;
                    top++;
                }

                for (int i = 0; i < M; ++i) {
                    long long current_val = 1LL * B[i] * (right_max_P[i] - left_min_P[i]);
                    if (current_val > ans) {
                        ans = current_val;
                    }
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
