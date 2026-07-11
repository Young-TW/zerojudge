#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, L;
    while (cin >> N >> K >> L) {
        double ans[40] = {0};
        bool has_any = false;
        double p_min = 0, p_max = 0;
        int total_color_sum = 0;
        double mid_dist[40] = {0};

        for (int i = 0; i < N; ++i) {
            int d, b;
            char dir;
            cin >> d >> b >> dir;

            if (dir == 'D') { // 向右
                ans[b] += (L - d);
                if (!has_any) {
                    has_any = true;
                    p_min = p_max = d;
                    total_color_sum = b % K;
                } else {
                    double new_mid[40] = {0};
                    for (int s = 0; s < K; ++s) {
                        if (mid_dist[s] != 0) {
                            new_mid[(b + s) % K] += mid_dist[s];
                        }
                    }
                    double gap = (d - p_max) / 2.0;
                    new_mid[b % K] += gap;
                    for (int s = 0; s < K; ++s) mid_dist[s] = new_mid[s];
                    p_max = d;
                    total_color_sum = (b + total_color_sum) % K;
                }
            } else { // 'L' 向左
                if (!has_any) {
                    ans[b] += d;
                } else {
                    double seg0 = (d - p_max) / 2.0;
                    ans[b] += seg0;
                    for (int s = 0; s < K; ++s) {
                        if (mid_dist[s] != 0) {
                            int c = (b + s) % K;
                            ans[c] += mid_dist[s];
                        }
                    }
                    double seg_last = (d + p_min) / 2.0;
                    int c_last = (b + total_color_sum) % K;
                    ans[c_last] += seg_last;
                }
            }
        }

        cout << fixed << setprecision(1);
        for (int i = 0; i < K; ++i) {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}
