#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int a[4];
    while (cin >> a[0] >> a[1] >> a[2] >> a[3]) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int g[4];
            cin >> g[0] >> g[1] >> g[2] >> g[3];
            int A = 0;
            int cntA[10] = {0}, cntG[10] = {0};
            for (int j = 0; j < 4; j++) {
                if (a[j] == g[j]) A++;
                else {
                    cntA[a[j]]++;
                    cntG[g[j]]++;
                }
            }
            int B = 0;
            for (int d = 0; d < 10; d++) B += min(cntA[d], cntG[d]);
            cout << A << "A" << B << "B\n";
        }
    }
    return 0;
}
