#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXX = 1000005;
int cnt[MAXX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N, X, V;
        cin >> N >> X >> V;
        V %= X;
        vector<int> used;
        used.reserve(N);
        for (int i = 0; i < N; ++i) {
            int C, D;
            cin >> C >> D;
            C %= X;
            int pos;
            if (D == 0) {
                pos = (C + V) % X;
            } else {
                pos = (C - V) % X;
                if (pos < 0) pos += X;
            }
            if (cnt[pos] == 0) {
                used.push_back(pos);
            }
            cnt[pos]++;
        }
        
        int max_dist = 0;
        if (N == 1) {
            max_dist = X;
        } else {
            if (used.size() * 20 < X) {
                sort(used.begin(), used.end());
                for (size_t i = 1; i < used.size(); ++i) {
                    max_dist = max(max_dist, used[i] - used[i-1]);
                }
                max_dist = max(max_dist, used[0] + X - used.back());
            } else {
                int last = -1;
                int first = -1;
                for (int i = 0; i < X; ++i) {
                    if (cnt[i] > 0) {
                        if (last == -1) {
                            first = i;
                        } else {
                            max_dist = max(max_dist, i - last);
                        }
                        last = i;
                    }
                }
                if (last != -1) {
                    max_dist = max(max_dist, first + X - last);
                }
            }
        }
        
        cout << max_dist << "\n";
        
        for (int pos : used) {
            cnt[pos] = 0;
        }
    }
    return 0;
}
