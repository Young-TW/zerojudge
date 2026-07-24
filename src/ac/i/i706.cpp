#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int BUFFER_SIZE = 1 << 20;

inline char read_char() {
    static char buffer[BUFFER_SIZE];
    static int pos = 0;
    static int len = 0;
    if (pos == len) {
        len = fread(buffer, 1, BUFFER_SIZE, stdin);
        pos = 0;
        if (len == 0) return EOF;
    }
    return buffer[pos++];
}

inline bool read_int(int &x) {
    char c = read_char();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == EOF) return false;
        c = read_char();
    }
    bool sign = false;
    if (c == '-') {
        sign = true;
        c = read_char();
    }
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = read_char();
    }
    if (sign) x = -x;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    
    int n;
    if (!read_int(n)) return 0;
    
    vector<int> h(n);
    for (int i = 0; i < n; ++i) {
        read_int(h[i]);
    }
    
    vector<int> ans(n);
    vector<int> st;
    st.reserve(n);
    
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && h[st.back()] >= h[i]) {
            st.pop_back();
        }
        if (st.empty()) {
            ans[i] = 0;
        } else {
            ans[i] = st.back() + 1;
        }
        st.push_back(i);
    }
    
    string out;
    out.reserve(n * 8);
    for (int i = 0; i < n; ++i) {
        out += to_string(ans[i]);
        out += (i == n - 1) ? '\n' : ' ';
    }
    
    fwrite(out.data(), 1, out.length(), stdout);
    
    return 0;
}
