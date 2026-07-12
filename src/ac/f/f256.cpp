#include <cstdio>

const int BUF_SIZE = 1 << 20;
char buf[BUF_SIZE];
int buf_pos = 0;
int buf_len = 0;

inline char get_char() {
    if (buf_pos == buf_len) {
        buf_len = fread(buf, 1, BUF_SIZE, stdin);
        buf_pos = 0;
        if (buf_len == 0) return EOF;
    }
    return buf[buf_pos++];
}

inline bool read_int(long long &num) {
    char c = get_char();
    while (c != EOF && (c < '0' || c > '9')) c = get_char();
    if (c == EOF) return false;
    
    num = 0;
    while (c >= '0' && c <= '9') {
        num = num * 10 + (c - '0');
        c = get_char();
    }
    return true;
}

int main() {
    long long total_score = 0;
    long long total_credit = 0;
    long long G, C;
    
    while (read_int(G)) {
        if (!read_int(C)) break;
        total_score += G * C;
        total_credit += C;
    }
    
    if (total_credit > 0) {
        long long avg = total_score / total_credit;
        if (avg >= 60) {
            printf("Oh wow! You pass it!\n%lld\n", avg);
        } else {
            printf("YEEEEEE!!!\n");
        }
    } else {
        printf("YEEEEEE!!!\n");
    }
    
    return 0;
}
