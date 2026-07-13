#include <iostream>
#include <cstdio>

using namespace std;

const int MAX_N = 10000;
int ans[MAX_N + 1];

void precompute() {
    int res = 1;
    int c2 = 0, c5 = 0;
    int pow2[] = {6, 2, 4, 8};
    ans[0] = 1;
    for (int i = 1; i <= MAX_N; ++i) {
        int x = i;
        while (x % 2 == 0) {
            c2++;
            x /= 2;
        }
        while (x % 5 == 0) {
            c5++;
            x /= 5;
        }
        res = (res * x) % 10;
        int diff = c2 - c5;
        int final_ans = res;
        if (diff > 0) {
            final_ans = (res * pow2[diff % 4]) % 10;
        }
        ans[i] = final_ans;
    }
}

int main() {
    precompute();
    int N;
    while (cin >> N) {
        printf("%5d -> %d\n", N, ans[N]);
    }
    return 0;
}
