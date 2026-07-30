#include <bits/stdc++.h>
using namespace std;

struct State {
    int a, b;
    State(int _a = 0, int _b = 0) : a(_a), b(_b) {}
};

int Ca, Cb, N;
vector<vector<char>> visited;
vector<State> path;

/* greatest common divisor, Euclidean algorithm */
int my_gcd(int x, int y) {
    while (y) {
        int t = x % y;
        x = y;
        y = t;
    }
    return x;
}

/* depth‑first search with the exact neighbour order required by the judge */
bool dfs(int a, int b) {
    if (visited[a][b]) return false;
    visited[a][b] = 1;
    path.emplace_back(a, b);
    if (a + b == N) return true;

    // 1) empty B
    if (b > 0 && dfs(a, 0)) return true;
    // 2) fill A
    if (a < Ca && dfs(Ca, b)) return true;
    // 3) pour A -> B until B is full
    if (a > 0 && b < Cb && a + b > Cb) {
        int na = a + b - Cb;
        int nb = Cb;
        if (dfs(na, nb)) return true;
    }
    // 4) pour B -> A until A is full
    if (a < Ca && b > 0 && a + b > Ca) {
        int na = Ca;
        int nb = a + b - Ca;
        if (dfs(na, nb)) return true;
    }
    // 5) pour A -> B until A becomes empty (fits into B)
    if (a > 0 && a + b <= Cb) {
        if (dfs(0, a + b)) return true;
    }
    // 6) fill B
    if (b < Cb && dfs(a, Cb)) return true;
    // 7) empty A
    if (a > 0 && dfs(0, b)) return true;
    // 8) pour B -> A until B becomes empty (fits into A)
    if (b > 0 && a + b <= Ca) {
        if (dfs(a + b, 0)) return true;
    }

    path.pop_back();          // backtrack
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> Ca >> Cb >> N) {
        if (N == 0) {
            cout << "(0,0)\n";
            continue;
        }
        if (N > Ca + Cb || N % my_gcd(Ca, Cb) != 0) {
            cout << "NO\n";
            continue;
        }

        visited.assign(Ca + 1, vector<char>(Cb + 1, 0));
        path.clear();

        if (dfs(0, 0)) {
            for (size_t i = 0; i < path.size(); ++i) {
                cout << '(' << path[i].a << ',' << path[i].b << ')';
                if (i + 1 != path.size()) cout << " -> ";
            }
            cout << '\n';
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
