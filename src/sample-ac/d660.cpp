#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N;
        cin >> N;
        int prev = 0;
        int high = 0, low = 0;
        for (int i = 0; i < N; ++i) {
            int h;
            cin >> h;
            if (i > 0) {
                if (h > prev) ++high;
                else if (h < prev) ++low;
            }
            prev = h;
        }
        cout << "Case " << t << ": " << high << " " << low << "\n";
    }
    return 0;
}
