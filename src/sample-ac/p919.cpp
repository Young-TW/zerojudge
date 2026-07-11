#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        vector<string> clubs(M);
        map<string, int> idx;
        vector<int> cnt(M, 0);
        
        for (int i = 0; i < M; i++) {
            cin >> clubs[i];
            idx[clubs[i]] = i;
        }
        
        for (int i = 0; i < N; i++) {
            set<int> chosen;
            for (int j = 0; j < 3; j++) {
                string s;
                cin >> s;
                chosen.insert(idx[s]);
            }
            for (set<int>::iterator it = chosen.begin(); it != chosen.end(); ++it) {
                cnt[*it]++;
            }
        }
        
        vector<pair<int, int> > order(M);
        for (int i = 0; i < M; i++) {
            order[i] = make_pair(cnt[i], i);
        }
        
        sort(order.begin(), order.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
            if (a.first != b.first) return a.first > b.first;
            return a.second < b.second;
        });
        
        for (int i = 0; i < M; i++) {
            cout << clubs[order[i].second] << " " << order[i].first << "\n";
        }
    }
    
    return 0;
}
