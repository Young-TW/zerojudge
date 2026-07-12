#include <cstdio>

const int BUFFER_SIZE = 1 << 16;
char buf[BUFFER_SIZE];
int buf_len = 0;
int buf_pos = 0;

inline int get_char() {
    if (buf_pos == buf_len) {
        buf_len = fread(buf, 1, BUFFER_SIZE, stdin);
        buf_pos = 0;
        if (buf_len == 0) return EOF;
    }
    return buf[buf_pos++];
}

int main() {
    int T = 0;
    int c = get_char();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t') c = get_char();
    while (c >= '0' && c <= '9') {
        T = T * 10 + (c - '0');
        c = get_char();
    }
    
    while (T--) {
        long long cnt_O = 0, cnt_Ow = 0, ans = 0;
        const long long MOD = 1000000007;
        
        while (c == ' ' || c == '\n' || c == '\r' || c == '\t') c = get_char();
        if (c == EOF) break;
        
        while (c != ' ' && c != '\n' && c != '\r' && c != '\t' && c != EOF) {
            if (c == 'O') {
                ans += cnt_Ow;
                if (ans >= MOD) ans -= MOD;
                cnt_O++;
                if (cnt_O >= MOD) cnt_O -= MOD;
            } else if (c == 'w') {
                cnt_Ow += cnt_O;
                if (cnt_Ow >= MOD) cnt_Ow -= MOD;
            }
            c = get_char();
        }
        
        printf("%lld\n", ans);
    }
    return 0;
}
