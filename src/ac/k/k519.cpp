#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const long long INF = (long long)1e15;

int N;
vector<vector<int>> price;
int startCity, targetCity;
long long best;
vector<bool> visited;

void dfs(int cur, long long curCost, int steps) {
    if (cur == targetCity) {
        if (curCost < best) best = curCost;
        return;
    }
    for (int nxt = 1; nxt <= N; ++nxt) {
        int p = price[cur][nxt];
        if (p == -1) continue;          // no direct flight
        if (visited[nxt]) continue;     // cannot reuse a city
        long long added = p;
        if (steps >= 1) added -= 50;    // discount for a transfer
        visited[nxt] = true;
        dfs(nxt, curCost + added, steps + 1);
        visited[nxt] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    if (!(cin >> N)) return 0;
    price.assign(N + 1, vector<int>(N + 1, -1));
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> price[i][j];
        }
    }
    cin >> startCity >> targetCity;

    best = INF;
    visited.assign(N + 1, false);
    visited[startCity] = true;
    dfs(startCity, 0LL, 0);

    cout << best << '\n';
    return 0;
}
