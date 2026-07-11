#include <cstdio>
#include <vector>

using namespace std;

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        vector<int> c(n);
        vector<vector<int>> dishes(n + 1);
        for (int i = 0; i < n; ++i) {
            int ci, di;
            scanf("%d %d", &ci, &di);
            c[i] = ci;
            dishes[di].push_back(i + 1);
        }
        
        vector<int> ptr(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            int dish = c[i];
            if (i > 0) {
                printf(" ");
            }
            printf("%d", dishes[dish][ptr[dish]++]);
        }
        printf("\n");
    }
    
    return 0;
}
