#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Player {
    string name;
    int hp;
    int dmg;
    vector<string> items;
    int next;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, S;
    if (!(cin >> N >> S)) return 0;

    vector<Player> players(N + 1);

    for (int i = 1; i <= N; ++i) {
        cin >> players[i].name >> players[i].hp >> players[i].dmg;
        players[i].items.resize(players[i].hp);
        for (int j = 0; j < players[i].hp; ++j) {
            cin >> players[i].items[j];
        }
        cin >> players[i].next;
    }

    vector<bool> visited(N + 1, false);
    vector<int> order;

    int curr = S;
    while (curr >= 1 && curr <= N && !visited[curr]) {
        visited[curr] = true;
        order.push_back(curr);

        int d = players[curr].dmg;
        players[curr].hp -= d;
        for (int i = 0; i < d && !players[curr].items.empty(); ++i) {
            players[curr].items.pop_back();
        }

        curr = players[curr].next;
    }

    for (int id : order) {
        if (players[id].hp <= 0) {
            cout << players[id].name << " dead.\n";
        } else {
            cout << players[id].name << " " << players[id].hp;
            for (const string& item : players[id].items) {
                cout << " " << item;
            }
            cout << "\n";
        }
    }

    return 0;
}
