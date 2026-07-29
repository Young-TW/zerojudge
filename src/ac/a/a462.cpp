#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
const ll INF = 1e18;
const int MOD1 = 1000000007;
const int MOD2 = 1000000009;
struct Edge {
int to;
ll w;
int id;
};
vector<ll> dijkstra(int s, vector<vector<Edge>>& adj, int N, int ban_edge = -1) {
vector<ll> dist(N+1, INF);
vector<bool> vis(N+1, false);
priority_queue<pli, vector<pli>, greater<pli>> pq;
dist[s] = 0;
pq.push({0, s});
while (!pq.empty()) {
int u = pq.top().second; pq.pop();
if (vis[u]) continue;
vis[u] = true;
for (auto& e : adj[u]) {
if (e.id == ban_edge) continue;
int v = e.to;
ll w = e.w;
if (dist[v] > dist[u] + w) {
dist[v] = dist[u] + w;
pq.push({dist[v], v});
}
}
}
return dist;
}
void dijkstra_tree(int s, vector<vector<Edge>>& adj, int N, vector<ll>& dist, vector<int>& parent, vector<int>& parent_edge) {
dist.assign(N+1, INF);
parent.assign(N+1, 0);
parent_edge.assign(N+1, -1);
vector<bool> vis(N+1, false);
priority_queue<pli, vector<pli>, greater<pli>> pq;
dist[s] = 0;
parent[s] = s;
pq.push({0, s});
while (!pq.empty()) {
int u = pq.top().second; pq.pop();
if (vis[u]) continue;
vis[u] = true;
for (auto& e : adj[u]) {
int v = e.to;
ll w = e.w;
if (dist[v] > dist[u] + w) {
dist[v] = dist[u] + w;
parent[v] = u;
parent_edge[v] = e.id;
pq.push({dist[v], v});
}
}
}
}
int main() {
ios_base::sync_with_stdio(false);
cin.tie(nullptr);
int N, M;
while (cin >> N >> M) {
vector<vector<Edge>> adj(N+1);
vector<ll> edge_w(M);
vector<pair<int, int>> edge_ends(M);
for (int i = 0; i < M; ++i) {
int u, v; ll w;
cin >> u >> v >> w;
adj[u].push_back({v, w, i});
adj[v].push_back({u, w, i});
edge_w[i] = w;
edge_ends[i] = {u, v};
}
if (N == 1) {
cout << 0 << '\n';
continue;
}
vector<ll> dist1;
vector<int> parent1, parent1_edge;
dijkstra_tree(1, adj, N, dist1, parent1, parent1_edge);
vector<ll> distN;
vector<int> parentN, parentN_edge;
dijkstra_tree(N, adj, N, distN, parentN, parentN_edge);
ll D = dist1[N];
if (D == INF) {
cout << 0 << '\n';
continue;
}
vector<pair<int, int>> dag_edges;
vector<vector<int>> dag_rev(N+1);
for (int i = 0; i < M; ++i) {
int u = edge_ends[i].first, v = edge_ends[i].second;
ll w = edge_w[i];
if (dist1[u] + w == dist1[v]) {
dag_edges.emplace_back(u, v);
dag_rev[v].push_back(u);
}
if (dist1[v] + w == dist1[u]) {
dag_edges.emplace_back(v, u);
dag_rev[u].push_back(v);
}
}
vector<int> cnt1_1(N+1, 0), cnt1_2(N+1, 0);
vector<int> order1;
for (int i = 1; i <= N; ++i) if (dist1[i] != INF) order1.push_back(i);
sort(order1.begin(), order1.end(), [&](int a, int b) { return dist1[a] < dist1[b]; });
cnt1_1[1] = 1; cnt1_2[1] = 1;
vector<vector<int>> dag_out(N+1);
for (auto& e : dag_edges) dag_out[e.first].push_back(e.second);
for (int u : order1) {
if (cnt1_1[u] == 0 && cnt1_2[u] == 0) continue;
for (int v : dag_out[u]) {
cnt1_1[v] = (cnt1_1[v] + cnt1_1[u]) % MOD1;
cnt1_2[v] = (cnt1_2[v] + cnt1_2[u]) % MOD2;
}
}
int total1 = cnt1_1[N], total2 = cnt1_2[N];
vector<int> cntN_1(N+1, 0), cntN_2(N+1, 0);
vector<int> orderN = order1;
reverse(orderN.begin(), orderN.end());
cntN_1[N] = 1; cntN_2[N] = 1;
for (int u : orderN) {
if (cntN_1[u] == 0 && cntN_2[u] == 0) continue;
for (int v : dag_rev[u]) {
cntN_1[v] = (cntN_1[v] + cntN_1[u]) % MOD1;
cntN_2[v] = (cntN_2[v] + cntN_2[u]) % MOD2;
}
}
vector<bool> is_cand(M, false);
int cand_cnt = 0;
for (int i = 0; i < M; ++i) {
int u = edge_ends[i].first, v = edge_ends[i].second;
ll w = edge_w[i];
bool ok = false;
if (dist1[u] + w == dist1[v] && dist1[v] + distN[v] == D) {
if ( (1LL * cnt1_1[u] * cntN_1[v] % MOD1) == total1 &&
(1LL * cnt1_2[u] * cntN_2[v] % MOD2) == total2 ) {
ok = true;
}
}
if (!ok && dist1[v] + w == dist1[u] && dist1[u] + distN[u] == D) {
if ( (1LL * cnt1_1[v] * cntN_1[u] % MOD1) == total1 &&
(1LL * cnt1_2[v] * cntN_2[u] % MOD2) == total2 ) {
ok = true;
}
}
if (ok) {
is_cand[i] = true;
++cand_cnt;
}
}
ll max_diff = 0;
if (cand_cnt <= 150) {
for (int i = 0; i < M; ++i) {
if (!is_cand[i]) continue;
vector<ll> new_dist = dijkstra(1, adj, N, i);
ll D_avoid = new_dist[N];
ll diff = 0;
if (D_avoid == INF) {
diff = edge_w[i];
} else {
diff = min(D_avoid - D, edge_w[i]);
}
if (diff > max_diff) max_diff = diff;
}
} else {
vector<int> chain1;
int cur = N;
while (cur != 1) {
chain1.push_back(cur);
cur = parent1[cur];
}
chain1.push_back(1);
reverse(chain1.begin(), chain1.end());
int K = chain1.size();
vector<int> pos1(N+1, -1);
for (int i = 0; i < K; ++i) pos1[chain1[i]] = i;
vector<int> chain_edge_id(K-1);
for (int i = 0; i < K-1; ++i) chain_edge_id[i] = parent1_edge[chain1[i+1]];
vector<int> chainN;
cur = 1;
while (cur != N) {
chainN.push_back(cur);
cur = parentN[cur];
}
chainN.push_back(N);
reverse(chainN.begin(), chainN.end());
int K2 = chainN.size();
vector<int> posN(N+1, -1);
for (int i = 0; i < K2; ++i) posN[chainN[i]] = i;
vector<int> rep1_idx(N+1, -1);
for (int v = 1; v <= N; ++v) {
if (dist1[v] == INF) continue;
int c = v;
while (pos1[c] == -1) c = parent1[c];
rep1_idx[v] = pos1[c];
}
vector<int> repN_idx(N+1, -1);
for (int v = 1; v <= N; ++v) {
if (distN[v] == INF) continue;
int c = v;
while (posN[c] == -1) c = parentN[c];
repN_idx[v] = posN[c];
}
vector<int> tn_b_idx(K-1, -1);
for (int i = 0; i < K-1; ++i) {
int b = chain1[i+1];
tn_b_idx[i] = repN_idx[b];
}
vector<ll> approx_avoid(K-1, INF);
for (int i = 0; i < M; ++i) {
int u = edge_ends[i].first, v = edge_ends[i].second;
ll w = edge_w[i];
if (dist1[u] == INF || dist1[v] == INF || distN[u] == INF || distN[v] == INF) continue;
int ru = rep1_idx[u], rv = rep1_idx[v];
if (ru < rv) {
ll L = dist1[u] + w + distN[v];
int idx_x = ru, idx_y = rv;
int idx_ny = repN_idx[v];
for (int j = idx_x; j <= idx_y - 1; ++j) {
if (tn_b_idx[j] > idx_ny) {
if (L < approx_avoid[j]) approx_avoid[j] = L;
}
}
}
if (rv < ru) {
ll L = dist1[v] + w + distN[u];
int idx_x = rv, idx_y = ru;
int idx_ny = repN_idx[u];
for (int j = idx_x; j <= idx_y - 1; ++j) {
if (tn_b_idx[j] > idx_ny) {
if (L < approx_avoid[j]) approx_avoid[j] = L;
}
}
}
}
vector<int> edge_to_chain_idx(M, -1);
for (int i = 0; i < K-1; ++i) {
edge_to_chain_idx[chain_edge_id[i]] = i;
}
for (int i = 0; i < K-1; ++i) {
int e_id = chain_edge_id[i];
ll D_avoid = approx_avoid[i];
if (D_avoid == INF) {
vector<ll> new_dist = dijkstra(1, adj, N, e_id);
D_avoid = new_dist[N];
} else if (D_avoid > D) {
if (!is_cand[e_id]) {
vector<ll> new_dist = dijkstra(1, adj, N, e_id);
D_avoid = new_dist[N];
}
} else {
continue;
}
ll diff = 0;
if (D_avoid == INF) {
diff = edge_w[e_id];
} else {
diff = min(D_avoid - D, edge_w[e_id]);
}
if (diff > max_diff) max_diff = diff;
}
for (int i = 0; i < M; ++i) {
if (!is_cand[i]) continue;
if (edge_to_chain_idx[i] != -1) continue;
vector<ll> new_dist = dijkstra(1, adj, N, i);
ll D_avoid = new_dist[N];
ll diff = 0;
if (D_avoid == INF) {
diff = edge_w[i];
} else {
diff = min(D_avoid - D, edge_w[i]);
}
if (diff > max_diff) max_diff = diff;
}
}
cout << max_diff << '\n';
}
return 0;
}
