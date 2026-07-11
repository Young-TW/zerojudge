#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <cstring>
using namespace std;

int cnt[100005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    bool first = true;
    while (cin >> n) {
        if (!first) cout << "\n";
        first = false;
        memset(cnt, 0, sizeof(cnt));
        queue<pair<int, vector<int> > > q;
        int distinct = 0;
        for (int i = 0; i < n; i++) {
            int t, k;
            cin >> t >> k;
            vector<int> pax(k);
            for (int j = 0; j < k; j++) {
                cin >> pax[j];
                if (cnt[pax[j]] == 0) distinct++;
                cnt[pax[j]]++;
            }
            q.push(make_pair(t, pax));
            while (!q.empty() && q.front().first <= t - 86400) {
                pair<int, vector<int> >& front = q.front();
                for (size_t j = 0; j < front.second.size(); j++) {
                    int x = front.second[j];
                    cnt[x]--;
                    if (cnt[x] == 0) distinct--;
                }
                q.pop();
            }
            cout << distinct << "\n";
        }
    }
    return 0;
}
