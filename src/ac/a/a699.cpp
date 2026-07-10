#include <cstdio>
#include <cstring>

const int MAXN = 671064;
bool isComposite[MAXN + 1];

void buildSieve() {
    memset(isComposite, 0, sizeof(isComposite));
    isComposite[0] = true;
    isComposite[1] = true;
    for (int i = 2; (long long)i * i <= MAXN; ++i) {
        if (!isComposite[i]) {
            for (int j = i * i; j <= MAXN; j += i) {
                isComposite[j] = true;
            }
        }
    }
}

int main() {
    buildSieve();
    int n;
    while (scanf("%d", &n) == 1) {
        if (!isComposite[n]) {
            printf("It's a prime!!!\n");
        } else {
            printf("It's not a prime!!!\n");
        }
    }
    return 0;
}
