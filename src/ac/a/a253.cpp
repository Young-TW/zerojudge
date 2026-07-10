#include <cstdio>
using namespace std;

int main() {
    static long long cnt[101] = {0};
    int s;
    long long n;
    while (scanf("%d", &s) == 1 && s != -1) {
        scanf("%lld", &n);
        cnt[s] += n;
    }
    while (scanf("%d", &s) == 1 && s != -1) {
        scanf("%lld", &n);
        cnt[s] += n;
    }
    for (int i = 0; i <= 100; ++i) {
        if (cnt[i] > 0) printf("%d %lld\n", i, cnt[i]);
    }
    return 0;
}
