#include <cstdio>
using namespace std;

int n;
char s[32];

void dfs(int o, int c, int k) {
    if (o == n && c == n) { s[k] = 0; printf("%s\n", s); return; }
    if (o < n) { s[k] = '('; dfs(o + 1, c, k + 1); }
    if (c < o) { s[k] = ')'; dfs(o, c + 1, k + 1); }
}

int main() {
    bool first = true;
    while (scanf("%d", &n) == 1) {
        if (!first) printf(" \n");
        first = false;
        dfs(0, 0, 0);
    }
    return 0;
}
