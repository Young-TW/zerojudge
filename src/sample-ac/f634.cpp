#include <cstdio>
#include <unordered_set>

using namespace std;

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) == 2) {
        unordered_set<unsigned long long> ust;
        ust.reserve(M * 2);
        
        int cnt_branch[4] = {0};
        int cnt_rank[4] = {0};
        
        char S[16];
        int A, B;
        
        for (int i = 0; i < M; ++i) {
            scanf("%s %d %d", S, &A, &B);
            unsigned long long key = 0;
            for (int j = 0; S[j]; ++j) {
                key = key * 27 + (S[j] - 'A' + 1);
            }
            key = key * 4 + A;
            key = key * 4 + B;
            
            if (ust.insert(key).second) {
                cnt_branch[A]++;
                cnt_rank[B]++;
            }
        }
        
        printf("navy:%d army:%d air:%d\n", cnt_branch[1], cnt_branch[2], cnt_branch[3]);
        printf("officer:%d sergeant:%d soldier:%d\n", cnt_rank[1], cnt_rank[2], cnt_rank[3]);
        printf("survival rate: %.1f%%\n", (double)ust.size() * 100.0 / N);
    }
    return 0;
}
