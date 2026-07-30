#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const int V = 12;
    const int E = 12;
    const int edges[E][2] = {
        {0, 3}, {1, 4}, {2, 3}, {3, 4}, {4, 5}, {3, 7},
        {4, 8}, {6, 7}, {7, 8}, {8, 9}, {7, 10}, {8, 11}
    };

    const int ALL = 1 << V;
    std::vector<char> dp(ALL, 0);
    dp[0] = 1;

    for (int mask = 1; mask < ALL; ++mask) {
        bool win = false;

        for (int i = 0; i < V; ++i) {
            if (mask & (1 << i)) {
                int nmask = mask ^ (1 << i);
                if (!dp[nmask]) {
                    win = true;
                    break;
                }
            }
        }

        if (!win) {
            for (int e = 0; e < E; ++e) {
                int take = (1 << edges[e][0]) | (1 << edges[e][1]);
                if ((mask & take) == take) {
                    int nmask = mask ^ take;
                    if (!dp[nmask]) {
                        win = true;
                        break;
                    }
                }
            }
        }

        dp[mask] = win ? 1 : 0;
    }

    int n;
    while (std::cin >> n) {
        std::string out;
        out.reserve(n);

        for (int i = 0; i < n; ++i) {
            std::string s;
            std::cin >> s;

            int mask = 0;
            for (int j = 0; j < V; ++j) {
                if (j < static_cast<int>(s.size()) && s[j] == '1') {
                    mask |= 1 << j;
                }
            }

            out.push_back(dp[mask] ? '1' : '0');
        }

        std::cout << out << '\n';
    }

    return 0;
}
