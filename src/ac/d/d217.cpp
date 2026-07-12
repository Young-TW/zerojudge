#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n && n != -1) {
        string answer, guess;
        cin >> answer >> guess;

        int unique_letters = 0;
        bool in_answer[26] = {false};
        for (char c : answer) {
            if (!in_answer[c - 'a']) {
                in_answer[c - 'a'] = true;
                unique_letters++;
            }
        }

        int wrong_count = 0;
        int guessed_correctly = 0;
        bool guessed[26] = {false};
        bool win = false, lose = false;

        for (char c : guess) {
            if (guessed[c - 'a']) continue;
            guessed[c - 'a'] = true;

            if (in_answer[c - 'a']) {
                guessed_correctly++;
                if (guessed_correctly == unique_letters) {
                    win = true;
                    break;
                }
            } else {
                wrong_count++;
                if (wrong_count == 7) {
                    lose = true;
                    break;
                }
            }
        }

        cout << "Round " << n << "\n";
        if (win) {
            cout << "You win.\n";
        } else if (lose) {
            cout << "You lose.\n";
        } else {
            cout << "You chickened out.\n";
        }
    }

    return 0;
}
