#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

int main() {
    long long dim, val;
    while (true) {
        std::vector<std::pair<long long, long long>> v1;
        bool eof = true;
        while (scanf("%lld:%lld", &dim, &val) == 2) {
            if (dim == 0 && val == 0) {
                eof = false;
                break;
            }
            v1.push_back({dim, val});
        }
        if (eof) break;

        std::sort(v1.begin(), v1.end());
        std::vector<std::pair<long long, long long>> unique_v1;
        for (size_t i = 0; i < v1.size(); ++i) {
            if (!unique_v1.empty() && unique_v1.back().first == v1[i].first) {
                unique_v1.back().second += v1[i].second;
            } else {
                unique_v1.push_back(v1[i]);
            }
        }

        long long ans = 0;
        while (scanf("%lld:%lld", &dim, &val) == 2) {
            if (dim == 0 && val == 0) {
                break;
            }
            auto it = std::lower_bound(unique_v1.begin(), unique_v1.end(), dim, [](const std::pair<long long, long long>& p, long long d) {
                return p.first < d;
            });
            if (it != unique_v1.end() && it->first == dim) {
                ans += it->second * val;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
