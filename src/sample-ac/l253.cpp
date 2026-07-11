#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const int MOD = 998244353;

inline int readInt() {
    int x = 0;
    char c = getchar();
    while (c != EOF && (c < '0' || c > '9')) c = getchar();
    if (c == EOF) return -1;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while ((N = readInt()) != -1) {
        vector<int> A(N + 1);
        for (int i = 1; i <= N; ++i) {
            A[i] = readInt();
        }
        
        vector<int> left(N + 1, 0);
        vector<int> right(N + 1, N + 1);
        
        vector<int> st;
        st.reserve(N);
        for (int i = 1; i <= N; ++i) {
            while (!st.empty() && A[st.back()] >= A[i]) {
                st.pop_back();
            }
            left[i] = st.empty() ? 0 : st.back();
            st.push_back(i);
        }
        
        st.clear();
        for (int i = N; i >= 1; --i) {
            while (!st.empty() && A[st.back()] > A[i]) {
                st.pop_back();
            }
            right[i] = st.empty() ? N + 1 : st.back();
            st.push_back(i);
        }
        
        long long ans = 0;
        for (int i = 1; i <= N; ++i) {
            long long l_cnt = i - left[i];
            long long r_cnt = right[i] - i;
            long long cnt = (l_cnt * r_cnt) % MOD;
            ans = (ans + (long long)A[i] * cnt) % MOD;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
