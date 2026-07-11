#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m, n || m) {
        vector<unordered_map<int, int>> vectors;
        bool rofu_turn = true;
        bool game_over = false;
        string winner;

        for (int i = 0; i < m; ++i) {
            int k;
            cin >> k;
            unordered_map<int, int> v;
            for (int j = 0; j < k; ++j) {
                int idx, val;
                char colon;
                cin >> idx >> colon >> val;
                v[idx] = val;
            }

            bool is_orthogonal = true;
            for (const auto& vec : vectors) {
                int dot = 0;
                for (const auto& [idx, val] : v) {
                    if (vec.count(idx)) {
                        dot += val * vec.at(idx);
                    }
                }
                if (dot != 0) {
                    is_orthogonal = false;
                    break;
                }
            }

            if (!is_orthogonal) {
                game_over = true;
                winner = rofu_turn ? "Yin" : "Rofu";
                break;
            }

            vectors.push_back(v);
            rofu_turn = !rofu_turn;
        }

        if (game_over) {
            cout << winner << '\n';
        } else {
            cout << "Hakuna matata\n";
        }
    }

    return 0;
}
