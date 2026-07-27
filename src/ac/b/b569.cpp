#include <cstdio>
#include <cstring>

int main() {
    static char s[10000001], cur[10000001];
    bool first = true;
    
    while (scanf("%s", s) == 1) {
        if (s[0] == '-') continue;
        scanf("%s", cur);
        
        int l = strlen(s);
        
        // num = s ^ cur (t的二进制表示，低位在前)
        for (int i = 0; i < l; i++) {
            cur[i] = (s[i] != cur[i]) ? '1' : '0';
        }
        // 二进制加1
        int i = 0;
        while (i < l && cur[i] == '1') {
            cur[i] = '0';
            i++;
        }
        if (i < l) cur[i] = '1';
        // result = s ^ num
        for (int i = 0; i < l; i++) {
            cur[i] = (s[i] != cur[i]) ? '1' : '0';
        }
        
        if (!first) {
            fwrite("\n----------------\n", 1, 18, stdout);
        }
        first = false;
        fwrite(cur, 1, l, stdout);
        fwrite("\n", 1, 1, stdout);
    }
    return 0;
}
