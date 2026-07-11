#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        int total_scores[4] = {0};
        for (int round = 1; round <= n; ++round) {
            int scores[4] = {0};
            bool has_double[4] = {false};
            int hearts_count[4] = {0};
            bool shoot_moon = false;

            for (int i = 0; i < 4; ++i) {
                string card;
                while (cin >> card && card != "#") {
                    char rank = card[0];
                    char suit = card[1];
                    if (suit == 'H') {
                        hearts_count[i]++;
                        if (rank == 'A') scores[i] += -50;
                        else if (rank == 'K') scores[i] += -40;
                        else if (rank == 'Q') scores[i] += -30;
                        else if (rank == 'J') scores[i] += -20;
                        else if (rank == 'T') scores[i] += -10;
                        else if (rank >= '5' && rank <= '9') scores[i] += -10;
                    } else if (suit == 'S') {
                        if (rank == 'Q') scores[i] += -100;
                    } else if (suit == 'D') {
                        if (rank == 'J') scores[i] += 100;
                    } else if (suit == 'C') {
                        if (rank == 'T') has_double[i] = true;
                    }
                }
            }

            for (int i = 0; i < 4; ++i) {
                if (hearts_count[i] == 13) {
                    shoot_moon = true;
                    break;
                }
            }

            if (shoot_moon) {
                for (int i = 0; i < 4; ++i) {
                    scores[i] = -scores[i];
                }
            }

            cout << "Round " << round << ":\n";
            for (int i = 0; i < 4; ++i) {
                if (has_double[i]) {
                    scores[i] *= 2;
                }
                total_scores[i] += scores[i];
                cout << "  " << i + 1 << ": " << scores[i] << "\n";
            }
        }

        cout << "Final:\n";
        for (int i = 0; i < 4; ++i) {
            cout << "  " << i + 1 << ": " << total_scores[i] << "\n";
        }
    }
    return 0;
}
