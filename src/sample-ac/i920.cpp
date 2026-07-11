#include <cstdio>

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    for (int i = 1; i <= N; ++i) {
        int h1, m1, h2, m2;
        int h3, m3, h4, m4;
        scanf("%d:%d %d:%d", &h1, &m1, &h2, &m2);
        scanf("%d:%d %d:%d", &h3, &m3, &h4, &m4);
        
        int w_start = h1 * 60 + m1;
        int w_end = h2 * 60 + m2;
        int m_start = h3 * 60 + m3;
        int m_end = h4 * 60 + m4;
        
        if (m_end < w_start || w_end < m_start) {
            printf("Case %d: Hits Meeting\n", i);
        } else {
            printf("Case %d: Mrs Meeting\n", i);
        }
    }
    return 0;
}
