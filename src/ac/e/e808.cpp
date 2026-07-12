#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        int h, m;
        cin >> h >> m;
        long long total = h * 60 + m;
        long long arrival[25];
        arrival[0] = total;
        for (int i = 1; i <= n; ++i) {
            int t;
            cin >> t;
            arrival[i] = arrival[i - 1] + t;
        }
        int q;
        while (cin >> q && q != 0) {
            long long time = arrival[q] % 1440;
            int hh = time / 60;
            int mm = time % 60;
            cout << setw(2) << setfill('0') << hh << ":"
                 << setw(2) << setfill('0') << mm << "\n";
        }
    }
    return 0;
}
