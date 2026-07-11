#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> mapping(N + 1);
        for (int i = 1; i <= N; ++i) {
            cin >> mapping[i];
        }

        vector<int> group(N + 1, -1);
        vector<int> group_size;
        vector<int> group_rep;
        vector<int> group_self_loop;

        for (int i = 1; i <= N; ++i) {
            if (group[i] != -1) continue;
            int cur = i;
            vector<int> path;
            while (group[cur] == -1) {
                group[cur] = -2;
                path.push_back(cur);
                cur = mapping[cur];
            }
            if (group[cur] == -2) {
                int rep = cur;
                int size = 0;
                bool self_loop = false;
                for (int j = path.size() - 1; j >= 0; --j) {
                    if (path[j] == rep) {
                        self_loop = (mapping[rep] == rep);
                        break;
                    }
                    size++;
                }
                size++;
                group_rep.push_back(rep);
                group_size.push_back(size);
                group_self_loop.push_back(self_loop);
                for (int node : path) {
                    if (node == rep) break;
                    group[node] = group_rep.size() - 1;
                }
                group[rep] = group_rep.size() - 1;
            } else {
                int g = group[cur];
                for (int node : path) {
                    group[node] = g;
                }
            }
        }

        int Q;
        cin >> Q;
        while (Q--) {
            int K;
            cin >> K;
            int g = group[K];
            if (group_self_loop[g]) {
                cout << "1\n";
            } else {
                if (group_size[g] % 2 == 1) {
                    cout << "1\n";
                } else {
                    cout << "-1\n";
                }
            }
        }
    }

    return 0;
}
