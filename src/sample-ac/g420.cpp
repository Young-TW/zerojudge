#include <cstdio>
#include <vector>

using namespace std;

int main() {
    int n;
    long long m;
    while (scanf("%d %lld", &n, &m) == 2) {
        vector<int> d(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &d[i]);
        }
        int ans = n;
        for (int i = 0; i < n; ++i) {
            int h;
            scanf("%d", &h);
            m -= d[i];
            if (m < 0) {
                ans = i + 1;
                for (int j = i + 1; j < n; ++j) {
                    scanf("%d", &h);
                }
                break;
            }
            m += h;
        }
        printf("%d\n", ans);
    }
    return 0;
}
