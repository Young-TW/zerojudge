#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        vector<int> B(M);
        for (int i = 0; i < M; ++i) {
            cin >> B[i];
        }

        vector<int> L(N, -1);
        vector<int> R(N, -1);
        vector<int> st;
        st.reserve(N);

        for (int i = 0; i < N; ++i) {
            while (!st.empty() && A[st.back()] < A[i]) {
                st.pop_back();
            }
            if (!st.empty()) {
                L[i] = st.back();
            }
            st.push_back(i);
        }

        st.clear();
        for (int i = N - 1; i >= 0; --i) {
            while (!st.empty() && A[st.back()] < A[i]) {
                st.pop_back();
            }
            if (!st.empty()) {
                R[i] = st.back();
            }
            st.push_back(i);
        }

        for (int i = 0; i < M; ++i) {
            int idx = B[i];
            int left_dist = (L[idx] == -1) ? N + 1 : (idx - L[idx]);
            int right_dist = (R[idx] == -1) ? N + 1 : (R[idx] - idx);
            int ans = min(left_dist, right_dist);
            if (ans > N) ans = 0;
            cout << ans << (i == M - 1 ? '\n' : ' ');
        }
    }

    return 0;
}
