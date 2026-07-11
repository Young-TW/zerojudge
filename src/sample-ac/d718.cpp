#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int team_id[1000000];
queue<int> team_queues[250005];
queue<int> main_queue;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    int case_num = 1;
    while (cin >> N) {
        while (!main_queue.empty()) {
            int t = main_queue.front();
            main_queue.pop();
            while (!team_queues[t].empty()) {
                team_queues[t].pop();
            }
        }

        memset(team_id, -1, sizeof(team_id));

        for (int i = 0; i < N; ++i) {
            int a;
            cin >> a;
            for (int j = 0; j < a; ++j) {
                int x;
                cin >> x;
                team_id[x] = i;
            }
        }

        cout << "Line #" << case_num++ << "\n";

        char cmd[15];
        int next_team_id = N;
        while (cin >> cmd) {
            if (cmd[0] == 'E') {
                int x;
                cin >> x;
                int t;
                if (team_id[x] != -1) {
                    t = team_id[x];
                } else {
                    t = next_team_id++;
                }
                if (team_queues[t].empty()) {
                    main_queue.push(t);
                }
                team_queues[t].push(x);
            } else if (cmd[0] == 'D') {
                int t = main_queue.front();
                int x = team_queues[t].front();
                team_queues[t].pop();
                if (team_queues[t].empty()) {
                    main_queue.pop();
                }
                cout << x << "\n";
            } else if (cmd[0] == 'S') {
                break;
            }
        }
    }
    return 0;
}
