#include <iostream>
#include <cstdio>

using namespace std;

int n;
char buf[50];
int buf_len;

inline void append_num(int num) {
    if (num < 10) {
        buf[buf_len++] = '0' + num;
    } else {
        buf[buf_len++] = '0' + num / 10;
        buf[buf_len++] = '0' + num % 10;
    }
}

void dfs(int i, __int128 sum, __int128 last_val) {
    if (i == n) {
        if (sum + last_val == 0) {
            buf[buf_len] = '\0';
            puts(buf);
        }
        return;
    }
    
    int next_i = i + 1;
    int prev_len = buf_len;
    
    __int128 pow10 = (next_i < 10) ? 10 : 100;
    
    // op = ' '
    buf[buf_len++] = ' ';
    append_num(next_i);
    __int128 new_last = (last_val >= 0) ? (last_val * pow10 + next_i) : (last_val * pow10 - next_i);
    dfs(next_i, sum, new_last);
    buf_len = prev_len;
    
    // op = '+'
    buf[buf_len++] = '+';
    append_num(next_i);
    dfs(next_i, sum + last_val, next_i);
    buf_len = prev_len;
    
    // op = '-'
    buf[buf_len++] = '-';
    append_num(next_i);
    dfs(next_i, sum + last_val, -next_i);
    buf_len = prev_len;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> n) {
        if (n < 3) continue;
        buf[0] = '1';
        buf_len = 1;
        dfs(1, 0, 1);
    }
    
    return 0;
}
