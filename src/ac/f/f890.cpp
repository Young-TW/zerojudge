#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <cctype>
#include <climits>
#include <limits>
#include <functional>
#include <utility>

using namespace std;

struct RelInfo {
    int delta;
    int gender;
    int age;
};

string normalize(const string& s) {
    istringstream iss(s);
    string word, res;
    while (iss >> word) {
        for (char& c : word) c = tolower(c);
        if (!res.empty()) res += ' ';
        res += word;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> priority(26);
    string order = "DABCEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 26; ++i) priority[order[i]-'A'] = i;

    map<string, RelInfo> relMap = {
        {"father", {1,0,0}},
        {"mother", {1,1,0}},
        {"parent", {1,-1,0}},
        {"son", {-1,0,0}},
        {"daughter", {-1,1,0}},
        {"child", {-1,-1,0}},
        {"grandpa", {2,0,0}},
        {"grandma", {2,1,0}},
        {"grandfather", {2,0,0}},
        {"grandmother", {2,1,0}},
        {"grandparent", {2,-1,0}},
        {"grandson", {-2,0,0}},
        {"granddaughter", {-2,1,0}},
        {"grandchild", {-2,-1,0}},
        {"older brother", {0,0,1}},
        {"big brother", {0,0,1}},
        {"older sister", {0,1,1}},
        {"big sister", {0,1,1}},
        {"younger brother", {0,0,-1}},
        {"younger sister", {0,1,-1}},
        {"brother", {0,0,0}},
        {"sister", {0,1,0}},
        {"cousin", {0,-1,0}},
        {"uncle", {1,0,0}},
        {"aunt", {1,1,0}},
        {"nephew", {-1,0,0}},
        {"niece", {-1,1,0}},
        {"husband", {0,0,0}},
        {"wife", {0,1,0}}
    };

    int N, M;
    while (cin >> N >> M) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<int> gender(N, -1);
        vector<vector<pair<int,int>>> genAdj(N);
        vector<pair<int,int>> ageEdges;
        bool bad = false;

        for (int i = 0; i < M; ++i) {
            string line;
            getline(cin, line);
            if (bad) continue;

            istringstream iss(line);
            char c1, c2;
            if (!(iss >> c1 >> c2)) { bad = true; continue; }
            string s;
            getline(iss, s);
            s = normalize(s);

            auto it = relMap.find(s);
            if (it == relMap.end()) { bad = true; continue; }

            int delta = it->second.delta;
            int g = it->second.gender;
            int age = it->second.age;

            int a = c1 - 'A';
            int b = c2 - 'A';
            if (a < 0 || a >= N || b < 0 || b >= N || a == b) { bad = true; continue; }

            if (g != -1) {
                if (gender[a] == -1) gender[a] = g;
                else if (gender[a] != g) { bad = true; }
            }

            genAdj[a].push_back({b, delta});
            genAdj[b].push_back({a, -delta});

            if (age == 1) {
                ageEdges.push_back({a, b});
            } else if (age == -1) {
                ageEdges.push_back({b, a});
            }
        }

        if (bad) {
            cout << "DD被整了!" << endl;
            continue;
        }

        vector<int> gen(N, INT_MAX);
        for (int i = 0; i < N && !bad; ++i) {
            if (gen[i] == INT_MAX) {
                gen[i] = 0;
                queue<int> q;
                q.push(i);
                while (!q.empty() && !bad) {
                    int u = q.front(); q.pop();
                    for (auto& p : genAdj[u]) {
                        int v = p.first;
                        int w = p.second;
                        int expected = gen[u] - w;
                        if (gen[v] == INT_MAX) {
                            gen[v] = expected;
                            q.push(v);
                        } else if (gen[v] != expected) {
                            bad = true;
                            break;
                        }
                    }
                }
            }
        }

        if (bad) {
            cout << "DD被整了!" << endl;
            continue;
        }

        for (auto& e : ageEdges) {
            if (gen[e.first] != gen[e.second]) {
                bad = true;
                break;
            }
        }

        if (bad) {
            cout << "DD被整了!" << endl;
            continue;
        }

        map<int, vector<int>, greater<int>> groups;
        for (int i = 0; i < N; ++i) {
            groups[gen[i]].push_back(i);
        }

        vector<vector<int>> answerLines;

        for (auto& kv : groups) {
            const vector<int>& nodes = kv.second;
            vector<vector<int>> localAgeAdj(N), localRevAgeAdj(N);
            vector<int> localOutdeg(N, 0);

            for (auto& e : ageEdges) {
                int u = e.first, v = e.second;
                if (find(nodes.begin(), nodes.end(), u) != nodes.end()) {
                    localAgeAdj[u].push_back(v);
                    localRevAgeAdj[v].push_back(u);
                    localOutdeg[u]++;
                }
            }

            vector<bool> used(N, false);
            vector<int> result;

            while (result.size() < nodes.size()) {
                int best = -1;
                for (int u : nodes) {
                    if (!used[u] && localOutdeg[u] == 0) {
                        if (best == -1 || priority[u] > priority[best]) {
                            best = u;
                        }
                    }
                }
                if (best == -1) {
                    bad = true;
                    break;
                }
                used[best] = true;
                result.push_back(best);
                for (int u : localRevAgeAdj[best]) {
                    localOutdeg[u]--;
                }
            }

            if (bad) break;
            reverse(result.begin(), result.end());
            answerLines.push_back(result);
        }

        if (bad) {
            cout << "DD被整了!" << endl;
            continue;
        }

        for (auto& line : answerLines) {
            for (size_t i = 0; i < line.size(); ++i) {
                if (i > 0) cout << ' ';
                cout << char('A' + line[i]);
            }
            cout << endl;
        }
    }

    return 0;
}
