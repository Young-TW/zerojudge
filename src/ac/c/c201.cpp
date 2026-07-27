#include <bits/stdc++.h>
using namespace std;

struct Player {
    string name;
    vector<int> scores;          // sorted descending
};

bool better(const Player& a, const Player& b) {
    size_t i = 0, na = a.scores.size(), nb = b.scores.size();
    while (i < na && i < nb) {
        if (a.scores[i] != b.scores[i])
            return a.scores[i] > b.scores[i];   // higher score wins
        ++i;
    }
    // all compared equal -> longer list wins
    return na > nb;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;          // no data

    vector<Player> players(N);
    for (int i = 0; i < N; ++i) {
        int K;
        cin >> players[i].name >> K;
        players[i].scores.resize(K);
        for (int j = 0; j < K; ++j) cin >> players[i].scores[j];
        sort(players[i].scores.begin(),
             players[i].scores.end(),
             greater<int>());
    }

    sort(players.begin(), players.end(), better);

    unordered_map<string, int> rank_of;
    int curRank = 1;
    rank_of[players[0].name] = curRank;
    for (int i = 1; i < N; ++i) {
        if (players[i].scores != players[i - 1].scores)
            ++curRank;                     // new distinct score list
        rank_of[players[i].name] = curRank;
    }

    string query;
    while (cin >> query) {
        cout << rank_of[query] << '\n';
    }
    return 0;
}
