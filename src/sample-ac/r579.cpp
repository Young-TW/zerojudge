#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    const int MAXN = 1000;
    int ans[MAXN + 1];
    
    for (int i = 1; i <= MAXN; ++i) {
        ans[i] = 4 * i + 2;
        for (int a = 1; a <= i; ++a) {
            if (i % a == 0) {
                int rem = i / a;
                for (int b = 1; b <= rem; ++b) {
                    if (rem % b == 0) {
                        int c = rem / b;
                        int area = 2 * (a * b + b * c + c * a);
                        if (area < ans[i]) {
                            ans[i] = area;
                        }
                    }
                }
            }
        }
    }
    
    int T;
    if (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            cout << ans[N] << "\n";
        }
    }
    return 0;
}
