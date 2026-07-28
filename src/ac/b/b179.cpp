#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1505;
const int MAXL = 105;
const int MOD = 10007;

int trie[MAXN][4];
int fail[MAXN];
bool term[MAXN];
int dep[MAXN];
int parent[MAXN];
int pchar[MAXN];
int next_node[MAXN];
int node_cnt;

int dp1[MAXN][MAXL], dp2[MAXN][MAXL];

void init_ac() {
    node_cnt = 1;
    memset(trie[0], 0, sizeof(trie[0]));
    term[0] = false;
    dep[0] = 0;
    parent[0] = -1;
    pchar[0] = -1;
    fail[0] = 0;
}

void insert_ac(const string& s) {
    int cur = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (!trie[cur][c]) {
            memset(trie[node_cnt], 0, sizeof(trie[node_cnt]));
            term[node_cnt] = false;
            dep[node_cnt] = dep[cur] + 1;
            parent[node_cnt] = cur;
            pchar[node_cnt] = c;
            trie[cur][c] = node_cnt++;
        }
        cur = trie[cur][c];
    }
    term[cur] = true;
}

void build_ac() {
    queue<int> q;
    for (int c = 0; c < 4; c++) {
        if (trie[0][c]) {
            fail[trie[0][c]] = 0;
            q.push(trie[0][c]);
        } else {
            trie[0][c] = 0;
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        term[u] = term[u] || term[fail[u]];
        for (int c = 0; c < 4; c++) {
            if (trie[u][c]) {
                int v = trie[u][c];
                fail[v] = trie[fail[u]][c];
                q.push(v);
            } else {
                trie[u][c] = trie[fail[u]][c];
            }
        }
    }
    next_node[0] = 0;
    for (int i = 1; i < node_cnt; i++) {
        if (dep[i] == 1) {
            next_node[i] = 0;
        } else {
            string s;
            int cur = i;
            while (cur != 0) {
                s.push_back('a' + pchar[cur]);
                cur = parent[cur];
            }
            reverse(s.begin(), s.end());
            string s2 = s.substr(1);
            int state = 0;
            for (char ch : s2) {
                state = trie[state][ch - 'a'];
            }
            next_node[i] = state;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string S;
    while (cin >> S) {
        int p, n;
        if (!(cin >> p >> n)) break;
        vector<string> patterns(n);
        for (int i = 0; i < n; i++) {
            cin >> patterns[i];
        }
        init_ac();
        for (const string& pat : patterns) {
            insert_ac(pat);
        }
        build_ac();
        
        int dead = 0, hospital = 0;
        int (*cur)[MAXL] = dp1;
        int (*nxt)[MAXL] = dp2;
        memset(cur, 0, sizeof(dp1));
        
        int state = 0;
        bool sick = false;
        for (char ch : S) {
            state = trie[state][ch - 'a'];
            if (term[state]) {
                sick = true;
                break;
            }
        }
        if (sick) {
            hospital = 1;
        } else {
            int L0 = S.size();
            if (L0 < MAXL) {
                cur[state][L0] = 1;
            }
        }
        
        for (int day = 0; day < p; day++) {
            memset(nxt, 0, sizeof(dp1));
            for (int node = 0; node < node_cnt; node++) {
                int d = dep[node];
                int startL = max(1, d);
                for (int L = startL; L < MAXL; L++) {
                    int cnt = cur[node][L];
                    if (cnt == 0) continue;
                    if (L == 1) {
                        dead += cnt;
                        if (dead >= MOD) dead -= MOD;
                    } else {
                        int newL = L - 1;
                        int new_node = (L > d) ? node : next_node[node];
                        if (term[new_node]) {
                            hospital += cnt;
                            if (hospital >= MOD) hospital -= MOD;
                        } else {
                            int& ref = nxt[new_node][newL];
                            ref += cnt;
                            if (ref >= MOD) ref -= MOD;
                        }
                    }
                    for (int c = 0; c < 4; c++) {
                        int nxt_state = trie[node][c];
                        if (term[nxt_state]) {
                            hospital += cnt;
                            if (hospital >= MOD) hospital -= MOD;
                        } else {
                            int newL = L + 1;
                            if (newL < MAXL) {
                                int& ref = nxt[nxt_state][newL];
                                ref += cnt;
                                if (ref >= MOD) ref -= MOD;
                            }
                        }
                    }
                }
            }
            swap(cur, nxt);
        }
        cout << dead % MOD << " " << hospital % MOD << "\n";
    }
    return 0;
}
