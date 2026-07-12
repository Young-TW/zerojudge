#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int BUFFER_SIZE = 1 << 20;
char buf[BUFFER_SIZE];
int buf_len = 0, buf_pos = 0;

inline int get_char() {
    if (buf_pos == buf_len) {
        buf_len = fread(buf, 1, BUFFER_SIZE, stdin);
        buf_pos = 0;
        if (buf_len == 0) return EOF;
    }
    return buf[buf_pos++];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int c;
    long long dp1 = 0, dp2 = 0, dp3 = 0;
    while ((c = get_char()) != EOF) {
        if (c == '1') {
            dp1++;
        } else if (c == '2') {
            if (dp1 > dp2) dp2 = dp1;
            dp2++;
        } else if (c == '3') {
            if (dp2 > dp3) dp3 = dp2;
            dp3++;
        } else if (c == '\n' || c == '\r') {
            break;
        }
    }
    
    long long ans = dp1;
    if (dp2 > ans) ans = dp2;
    if (dp3 > ans) ans = dp3;
    
    cout << ans << "\n";
    return 0;
}
