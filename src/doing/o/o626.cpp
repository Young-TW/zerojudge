#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

struct File {
    int a, b, c, d;
    int id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        vector<File> files(N);
        for (int i = 0; i < N; ++i) {
            cin >> files[i].a >> files[i].b >> files[i].c >> files[i].d;
            files[i].id = i;
        }
        vector<int> seq(M);
        for (int i = 0; i < M; ++i) {
            cin >> seq[i];
        }
        int last[5];
        for (int i = 1; i <= 4; ++i) last[i] = -1;
        for (int i = 0; i < M; ++i) {
            int x = seq[i];
            if (x >= 1 && x <= 4) {
                last[x] = i;
            }
        }
        vector<pair<int, int>> attrs;
        for (int attr = 1; attr <= 4; ++attr) {
            if (last[attr] != -1) {
                attrs.push_back({last[attr], attr});
            }
        }
        sort(attrs.begin(), attrs.end(), [](const pair<int,int>& p1, const pair<int,int>& p2) {
            return p1.first > p2.first;
        });
        auto getValue = [&](const File& f, int attr) -> int {
            switch(attr) {
                case 1: return f.a;
                case 2: return f.b;
                case 3: return f.c;
                case 4: return f.d;
                default: return 0;
            }
        };
        sort(files.begin(), files.end(), [&](const File& f1, const File& f2) {
            for (size_t i = 0; i < attrs.size(); ++i) {
                int attr = attrs[i].second;
                int dir = (i % 2 == 0) ? -1 : 1;
                int v1 = getValue(f1, attr);
                int v2 = getValue(f2, attr);
                if (v1 != v2) {
                    if (dir == -1) return v1 > v2;
                    else return v1 < v2;
                }
            }
            return f1.id < f2.id;
        });
        for (const auto& f : files) {
            cout << f.a << " " << f.b << " " << f.c << " " << f.d << "\n";
        }
    }
    return 0;
}
