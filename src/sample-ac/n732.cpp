#include <iostream>

using namespace std;

const int MAXN = 1000000;
int div_count[MAXN + 1];
int ans[MAXN + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    for (int i = 1; i <= MAXN; ++i) {
        for (int j = i; j <= MAXN; j += i) {
            div_count[j]++;
        }
    }
    
    ans[1] = 1;
    for (int i = 2; i <= MAXN; ++i) {
        if (div_count[i] >= div_count[ans[i-1]]) {
            ans[i] = i;
        } else {
            ans[i] = ans[i-1];
        }
    }
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            cout << ans[N] << '\n';
        }
    }
    
    return 0;
}
