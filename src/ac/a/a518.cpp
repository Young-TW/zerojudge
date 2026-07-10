#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main() {
    int a, b;
    while (scanf("%d %d", &a, &b) == 2) {
        if (a == -1 && b == -1) break;
        int d = abs(a - b);
        printf("%d\n", min(d, 100 - d));
    }
    return 0;
}
