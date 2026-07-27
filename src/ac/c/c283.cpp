#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <algorithm>

using namespace std;

int N, M;
vector<vector<int>> initial_piles;
map<vector<int>, double> memo;

double solve(vector<int> state) {
    int total_cards = 0;
    for (int i = 0; i < N; ++i) {
        total_cards += state[i];
    }
    if (total_cards == 0) return 1.0;

    if (memo.count(state)) return memo[state];

    vector<pair<int, int>> top_cards;
    for (int i = 0; i < N; ++i) {
        if (state[i] > 0) {
            top_cards.push_back({initial_piles[i][state[i] - 1], i});
        }
    }

    vector<pair<int, int>> valid_moves;
    int K = top_cards.size();
    for (int i = 0; i < K; ++i) {
        for (int j = i + 1; j < K; ++j) {
            int c1 = top_cards[i].first;
            int c2 = top_cards[j].first;
            if ((c1 & 0xFF) == (c2 & 0xFF) || (c1 >> 8) == (c2 >> 8)) {
                valid_moves.push_back({top_cards[i].second, top_cards[j].second});
            }
        }
    }

    if (valid_moves.empty()) return 0.0;

    double expected_value = 0.0;
    for (auto move : valid_moves) {
        vector<int> next_state = state;
        next_state[move.first]--;
        next_state[move.second]--;
        expected_value += solve(next_state);
    }
    expected_value /= valid_moves.size();

    memo[state] = expected_value;
    return expected_value;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> N >> M) {
        if (N == 0 && M == 0) break;

        initial_piles.assign(N, vector<int>(M));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                string card;
                cin >> card;
                int rank_val = 0;
                char r = card[0];
                if (r == 'A') rank_val = 1;
                else if (r >= '2' && r <= '9') rank_val = r - '0';
                else if (r == 'T') rank_val = 10;
                else if (r == 'J') rank_val = 11;
                else if (r == 'Q') rank_val = 12;
                else if (r == 'K') rank_val = 13;

                int suit_val = 0;
                char s = card[1];
                if (s == 'S') suit_val = 1;
                else if (s == 'C') suit_val = 2;
                else if (s == 'D') suit_val = 3;
                else if (s == 'H') suit_val = 4;

                initial_piles[i][j] = (suit_val << 8) | rank_val;
            }
        }

        memo.clear();
        vector<int> start_state(N, M);
        double probability = solve(start_state);

        cout << fixed << setprecision(6) << probability << "\n";
    }

    return 0;
}
