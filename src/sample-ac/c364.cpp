#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

inline bool readInt(int &x) {
    x = 0;
    char c = getchar();
    while (c != EOF && (c < '0' || c > '9')) {
        c = getchar();
    }
    if (c == EOF) return false;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return true;
}

inline void writeLL(long long x) {
    if (x == 0) {
        putchar('0');
        putchar('\n');
        return;
    }
    char buf[20];
    int len = 0;
    while (x > 0) {
        buf[len++] = x % 10 + '0';
        x /= 10;
    }
    while (len > 0) {
        putchar(buf[--len]);
    }
    putchar('\n');
}

int main() {
    int N;
    while (readInt(N)) {
        vector<int> h(N + 1);
        vector<long long> prefix_sum(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            readInt(h[i]);
            prefix_sum[i] = prefix_sum[i - 1] + h[i];
        }
        
        vector<int> L(N + 1, 0);
        vector<int> R(N + 1, 0);
        
        vector<int> st;
        st.reserve(N);
        
        for (int i = 1; i <= N; ++i) {
            while (!st.empty() && h[st.back()] < h[i]) {
                st.pop_back();
            }
            L[i] = st.empty() ? 0 : st.back();
            st.push_back(i);
        }
        
        st.clear();
        for (int i = N; i >= 1; --i) {
            while (!st.empty() && h[st.back()] < h[i]) {
                st.pop_back();
            }
            R[i] = st.empty() ? N + 1 : st.back();
            st.push_back(i);
        }
        
        for (int i = 1; i <= N; ++i) {
            long long left_sum = prefix_sum[i - 1] - prefix_sum[L[i]];
            long long right_sum = prefix_sum[R[i] - 1] - prefix_sum[i];
            writeLL(left_sum + right_sum);
        }
    }
    return 0;
}
