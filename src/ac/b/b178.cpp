#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>

struct Event {
    int time;
    int type;   // +1 = arrival, -1 = departure
    int id;
    bool operator<(const Event& other) const {
        return time < other.time;
    }
};

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        std::vector<int> A(n), B(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &A[i], &B[i]);
        }

        std::vector<Event> ev;
        ev.reserve(2 * n);
        for (int i = 0; i < n; ++i) {
            ev.push_back({A[i], +1, i});
            ev.push_back({B[i], -1, i});
        }
        std::sort(ev.begin(), ev.end());

        std::vector<char> active(n, 0);
        int answer = 0;

        for (const auto& e : ev) {
            if (e.type == +1) active[e.id] = 1;
            else            active[e.id] = 0;

            // collect active intervals
            std::vector<std::pair<int,int>> cur;
            cur.reserve(n);
            for (int i = 0; i < n; ++i) {
                if (active[i]) cur.emplace_back(A[i], B[i]);
            }
            if (cur.empty()) {
                answer = std::max(answer, 0);
                continue;
            }

            std::sort(cur.begin(), cur.end(),
                      [](const std::pair<int,int>& p1,
                         const std::pair<int,int>& p2) {
                          return p1.first < p2.first;
                      });

            // LIS of the B's (strictly increasing)
            std::vector<int> tails;
            tails.reserve(cur.size());
            for (const auto& p : cur) {
                int x = p.second;
                auto it = std::lower_bound(tails.begin(), tails.end(), x);
                if (it == tails.end())
                    tails.push_back(x);
                else
                    *it = x;
            }
            answer = std::max(answer, (int)tails.size());
        }

        printf("%d\n", answer);
    }
    return 0;
}
