#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        vector<string> clubs(M);
        unordered_map<string, int> club_to_idx;
        club_to_idx.reserve(M * 2);
        for (int i = 0; i < M; ++i) {
            cin >> clubs[i];
            club_to_idx[clubs[i]] = i;
        }

        vector<int> counts(M, 0);
        for (int i = 0; i < N; ++i) {
            string c1, c2, c3;
            cin >> c1 >> c2 >> c3;
            
            auto it1 = club_to_idx.find(c1);
            if (it1 != club_to_idx.end()) {
                counts[it1->second]++;
            }
            
            if (c2 != c1) {
                auto it2 = club_to_idx.find(c2);
                if (it2 != club_to_idx.end()) {
                    counts[it2->second]++;
                }
            }
            
            if (c3 != c1 && c3 != c2) {
                auto it3 = club_to_idx.find(c3);
                if (it3 != club_to_idx.end()) {
                    counts[it3->second]++;
                }
            }
        }

        vector<pair<int, int>> sorted_clubs(M);
        for (int i = 0; i < M; ++i) {
            sorted_clubs[i] = {counts[i], i};
        }

        sort(sorted_clubs.begin(), sorted_clubs.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) {
                return a.first > b.first;
            }
            return a.second < b.second;
        });

        for (int i = 0; i < M; ++i) {
            cout << clubs[sorted_clubs[i].second] << " " << sorted_clubs[i].first << "\n";
        }
    }

    return 0;
}
