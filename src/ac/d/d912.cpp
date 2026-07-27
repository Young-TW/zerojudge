#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 10005;
int N;
int D[MAXN];
int adj[MAXN][2];
int deg[MAXN];
int matchL[MAXN], matchR[MAXN];
int visL[MAXN], visR[MAXN];
int cur_vis_time;
int min_idx, locked_i;
int que[MAXN];
int preL[MAXN], preR[MAXN];

bool bfs(int start) {
    int head = 0, tail = 0;
    que[tail++] = start;
    visL[start] = cur_vis_time;
    preL[start] = -1;
    while (head < tail) {
        int u = que[head++];
        for (int k = 0; k < deg[u]; ++k) {
            int w = adj[u][k];
            if (visR[w] == cur_vis_time) continue;
            visR[w] = cur_vis_time;
            preR[w] = u;
            if (matchR[w] == -1) {
                int cur_w = w;
                while (cur_w != -1) {
                    int cur_u = preR[cur_w];
                    int next_w = preL[cur_u];
                    matchL[cur_u] = cur_w;
                    matchR[cur_w] = cur_u;
                    cur_w = next_w;
                }
                return true;
            } else {
                int nxt = matchR[w];
                if (nxt >= min_idx && nxt != locked_i) {
                    if (visL[nxt] != cur_vis_time) {
                        visL[nxt] = cur_vis_time;
                        preL[nxt] = w;
                        que[tail++] = nxt;
                    }
                }
            }
        }
    }
    return false;
}

bool try_improve(int i, int v) {
    int old = matchL[i];
    int j = matchR[v];
    if (j == -1) return false;
    matchL[i] = v; matchR[v] = i;
    matchL[j] = -1; matchR[old] = -1;
    min_idx = i;
    locked_i = i;
    ++cur_vis_time;
    if (bfs(j)) {
        return true;
    } else {
        matchL[i] = old; matchR[old] = i;
        matchL[j] = v; matchR[v] = j;
        return false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> N) {
        for (int i = 0; i < N; ++i) cin >> D[i];
        for (int i = 0; i < N; ++i) {
            int d = D[i];
            int c1 = (i + d) % N;
            int c2 = (i - d + N) % N;
            deg[i] = 0;
            int diff1 = i > c1 ? i - c1 : c1 - i;
            int dist1 = diff1 < N - diff1 ? diff1 : N - diff1;
            if (dist1 == d) {
                adj[i][deg[i]++] = c1;
            }
            if (c1 != c2) {
                int diff2 = i > c2 ? i - c2 : c2 - i;
                int dist2 = diff2 < N - diff2 ? diff2 : N - diff2;
                if (dist2 == d) {
                    adj[i][deg[i]++] = c2;
                }
            }
            if (deg[i] == 2 && adj[i][0] > adj[i][1]) {
                int tmp = adj[i][0];
                adj[i][0] = adj[i][1];
                adj[i][1] = tmp;
            }
        }
        memset(matchL, -1, sizeof(matchL));
        memset(matchR, -1, sizeof(matchR));
        memset(visL, 0, sizeof(visL));
        memset(visR, 0, sizeof(visR));
        cur_vis_time = 0;
        min_idx = 0;
        locked_i = -1;
        bool possible = true;
        for (int i = 0; i < N; ++i) {
            ++cur_vis_time;
            if (!bfs(i)) {
                possible = false;
                break;
            }
        }
        if (!possible) {
            cout << "No Answer" << endl;
            continue;
        }
        for (int i = 0; i < N; ++i) {
            for (int k = 0; k < deg[i]; ++k) {
                int v = adj[i][k];
                if (v == matchL[i]) break;
                if (matchR[v] < i) continue;
                if (try_improve(i, v)) break;
            }
        }
        for (int i = 0; i < N; ++i) {
            if (i > 0) cout << " ";
            cout << matchL[i];
        }
        cout << endl;
    }
    return 0;
}
