#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

vector<int> build_suffix_array(const string &s) {
    int n = s.size();
    vector<int> sa(n), rank(n), new_rank(n);
    for (int i = 0; i < n; ++i) {
        sa[i] = i;
        rank[i] = s[i];
    }

    for (int k = 1; k < n; k *= 2) {
        auto cmp = [&](int i, int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = (i + k < n) ? rank[i + k] : -1;
            int rj = (j + k < n) ? rank[j + k] : -1;
            return ri < rj;
        };
        sort(sa.begin(), sa.end(), cmp);

        new_rank[sa[0]] = 0;
        for (int i = 1; i < n; ++i) {
            new_rank[sa[i]] = new_rank[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        rank.swap(new_rank);
    }
    return sa;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string s;
        int K;
        cin >> s >> K;
        int n = s.size();
        s += s;
        vector<int> sa = build_suffix_array(s);

        int count = 0;
        for (int i = 0; i < sa.size(); ++i) {
            if (sa[i] < n) {
                count++;
                if (count == K) {
                    cout << s.substr(sa[i], n) << '\n';
                    break;
                }
            }
        }
    }
    return 0;
}
