#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        vector<vector<pair<int, int>>> floors(N, vector<pair<int, int>>(M));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> floors[i][j].first >> floors[i][j].second;
            }
        }

        int start;
        cin >> start;

        int key = 0;
        int current_room = start;
        for (int i = 0; i < N; ++i) {
            int x = floors[i][current_room].second;
            int stair_count = 0;
            int next_room = current_room;
            int steps = 0;
            while (steps < x) {
                if (floors[i][next_room].first == 1) {
                    steps++;
                    if (steps == x) {
                        break;
                    }
                }
                next_room = (next_room + 1) % M;
            }
            key = (key + floors[i][current_room].second) % 20123;
            current_room = next_room;
        }

        cout << key << '\n';
    }

    return 0;
}
