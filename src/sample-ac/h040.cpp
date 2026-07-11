#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int get_log2(long long x) {
    int res = 0;
    while (x > 1) {
        x >>= 1;
        res++;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<pair<int, long long>> events;
        for (int i = 0; i < N; ++i) {
            long long F;
            cin >> F;
            int c = get_log2(F + 1);
            if (c > 30) c = 30;
            if (!events.empty() && events.back().first == c) {
                events.back().second++;
            } else {
                events.push_back({c, 1});
            }
        }
        
        int Q;
        cin >> Q;
        while (Q--) {
            long long K;
            cin >> K;
            long long low = 1, high = K, ans = K;
            while (low <= high) {
                long long mid = low + (high - low) / 2;
                long long sum = mid;
                long long v = mid;
                for (auto &e : events) {
                    int c = e.first;
                    long long cnt = e.second;
                    if (c == 30) {
                        if (v > 0) {
                            if ((K - sum) / v <= cnt) {
                                sum = K;
                                break;
                            } else {
                                sum += v * cnt;
                            }
                        } else {
                            break;
                        }
                    } else {
                        for (long long j = 0; j < cnt; ++j) {
                            v = v * c / 30;
                            sum += v;
                            if (sum >= K) break;
                            if (v == 0) break;
                        }
                    }
                    if (sum >= K) break;
                    if (v == 0) break;
                }
                if (sum >= K) {
                    ans = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
