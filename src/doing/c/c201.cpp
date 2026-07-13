#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

struct Player {
    string name;
    vector<int> scores;

    // 排序規則：分數由高到低
    bool operator<(const Player& other) const {
        size_t i = 0;
        while (i < scores.size() && i < other.scores.size()) {
            if (scores[i] != other.scores[i]) {
                return scores[i] > other.scores[i]; // 分數高的排名前面
            }
            i++;
        }
        // 若前 min_size 個分數都相同，遊戲場次多的排名前面
        return scores.size() > other.scores.size();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    vector<Player> players(N);
    for (int i = 0; i < N; ++i) {
        int K;
        cin >> players[i].name >> K;
        players[i].scores.resize(K);
        for (int j = 0; j < K; ++j) {
            cin >> players[i].scores[j];
        }
        // 將分數由大到小排序
        sort(players[i].scores.begin(), players[i].scores.end(), greater<int>());
    }

    // 排序所有玩家
    sort(players.begin(), players.end());

    string query;
    while (cin >> query) {
        int rank = 1;
        for (int i = 0; i < N; ++i) {
            if (players[i].name == query) {
                cout << rank << "\n";
                break;
            }
            // 如果當前玩家與下一個玩家分數完全相同（包含場次），則排名相同
            if (i < N - 1) {
                bool same = true;
                if (players[i].scores.size() != players[i+1].scores.size()) {
                    same = false;
                } else {
                    for (size_t k = 0; k < players[i].scores.size(); ++k) {
                        if (players[i].scores[k] != players[i+1].scores[k]) {
                            same = false;
                            break;
                        }
                    }
                }
                if (!same) {
                    rank = i + 2;
                }
            }
        }
    }

    return 0;
}
