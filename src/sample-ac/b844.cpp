#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, Q;
    while (scanf("%d %d", &N, &Q) == 2) {
        vector<int> K(N);
        for (int i = 0; i < N; ++i) {
            scanf("%d", &K[i]);
        }
        sort(K.begin(), K.end());
        
        for (int i = 0; i < Q; ++i) {
            int P;
            scanf("%d", &P);
            int cnt = upper_bound(K.begin(), K.end(), P) - K.begin();
            printf("%d\n", cnt % 2);
        }
    }
    return 0;
}
