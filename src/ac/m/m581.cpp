#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    if (!(std::cin >> N)) return 0;               // no input

    std::vector<int> role(N + 1);
    int aliveWerewolf = 0;
    for (int i = 1; i <= N; ++i) {
        std::cin >> role[i];
        if (role[i] == -1) ++aliveWerewolf;
    }

    std::vector<char> dead(N + 1, 0);
    bool wrong = false;
    int x;
    while (std::cin >> x) {
        if (x == 0) break;                        // game ends
        if (x < 1 || x > N) {                     // out of range
            wrong = true;
            break;
        }
        if (dead[x]) {                            // duplicate elimination
            wrong = true;
            break;
        }
        dead[x] = 1;
        if (role[x] == -1) --aliveWerewolf;
    }

    if (wrong) {
        std::cout << "Wrong\n";
    } else if (aliveWerewolf > 0) {
        std::cout << "Werewolves\n";
    } else {
        std::cout << "Townsfolk\n";
    }
    return 0;
}
