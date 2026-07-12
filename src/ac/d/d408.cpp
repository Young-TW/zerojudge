#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        if (N == 0) break;
        for (int i = 0; i < N; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            int sum_sq = a * a + b * b + c * c;
            printf("%.1f\n", sum_sq / 3.0);
        }
    }
    
    return 0;
}
