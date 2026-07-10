#include <iostream>
#include <vector>

long long cost(long long f, bool same) {
    if (same) return f;
    if (f <= 1000) return 3 * f;
    return 3 * 1000 + 2 * (f - 1000);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::vector<long long>> q(n, std::vector<long long>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            std::cin >> q[i][j];

    long long best = -1;
    std::vector<int> c(n);
    for (int p = 0; p < k; p++) {
        for (int i = 0; i < n; i++)
            std::cin >> c[i];

        // accumulate flow per (source city u, dest city v)
        std::vector<std::vector<long long>> flow(m, std::vector<long long>(m, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                flow[c[i]][j] += q[i][j];

        long long total = 0;
        for (int u = 0; u < m; u++)
            for (int v = 0; v < m; v++)
                if (flow[u][v] > 0)
                    total += cost(flow[u][v], u == v);

        if (best < 0 || total < best) best = total;
    }

    std::cout << best << "\n";
    return 0;
}
