#include <iostream>
#include <cstring>

using namespace std;

int ans[105];

void precompute() {
    for (int N = 13; N < 100; N++) {
        for (int m = 1; ; m++) {
            bool off[105];
            memset(off, false, sizeof(off));
            int curr = 1;
            off[1] = true;
            bool valid = true;
            for (int step = 1; step < N; step++) {
                int count = 0;
                while (count < m) {
                    curr++;
                    if (curr > N) curr = 1;
                    if (!off[curr]) count++;
                }
                off[curr] = true;
                if (curr == 13) {
                    if (step != N - 1) {
                        valid = false;
                        break;
                    }
                }
            }
            if (valid && curr == 13) {
                ans[N] = m;
                break;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    int N;
    while (cin >> N && N) {
        cout << ans[N] << "\n";
    }
    return 0;
}
