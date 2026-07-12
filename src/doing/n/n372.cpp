#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    while (cin >> N) {
        vector<int> p0(N), p1(N);
        vector<int> pos0(N + 1), pos1(N + 1);

        for (int i = 0; i < N; ++i) {
            cin >> p0[i];
            pos0[p0[i]] = i;
        }

        for (int i = 0; i < N; ++i) {
            cin >> p1[i];
            pos1[p1[i]] = i;
        }

        long long min_dist = -1;
        long long count = 0;

        for (int a = 1; a <= N; ++a) {
            for (int b = a + 1; b <= N; ++b) {
                int i0 = pos0[a];
                int j0 = pos0[b];
                int i1 = pos1[a];
                int j1 = pos1[b];

                long long dist = abs(i0 - j0) + abs(i1 - j1);

                if (min_dist == -1 || dist < min_dist) {
                    min_dist = dist;
                    count = 1;
                } else if (dist == min_dist) {
                    count++;
                }
            }
        }

        cout << min_dist << " " << count << "\n";
    }

    return 0;
}
