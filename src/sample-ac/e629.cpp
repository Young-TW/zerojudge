#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int ans[1005];
    for (int i = 0; i <= 1000; ++i) {
        ans[i] = -1;
    }
    
    for (int i = 1; i <= 1000; ++i) {
        int sum = 0;
        for (int j = 1; j * j <= i; ++j) {
            if (i % j == 0) {
                sum += j;
                if (j * j != i) {
                    sum += i / j;
                }
            }
        }
        if (sum <= 1000) {
            ans[sum] = i;
        }
    }
    
    int S;
    int case_num = 1;
    while (cin >> S && S) {
        cout << "Case " << case_num << ": " << ans[S] << "\n";
        case_num++;
    }
    
    return 0;
}
