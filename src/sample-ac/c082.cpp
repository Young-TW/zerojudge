#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int W, H;
    if (!(cin >> W >> H)) return 0;

    bool scent[55][55] = {};
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    char dir_name[] = {'N', 'E', 'S', 'W'};

    int x, y;
    char dir_char;
    string instructions;

    while (cin >> x >> y >> dir_char >> instructions) {
        int dir;
        if (dir_char == 'N') dir = 0;
        else if (dir_char == 'E') dir = 1;
        else if (dir_char == 'S') dir = 2;
        else dir = 3;

        bool lost = false;
        for (char c : instructions) {
            if (c == 'L') {
                dir = (dir + 3) % 4;
            } else if (c == 'R') {
                dir = (dir + 1) % 4;
            } else if (c == 'F') {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if (nx < 0 || nx > W || ny < 0 || ny > H) {
                    if (!scent[x][y]) {
                        scent[x][y] = true;
                        lost = true;
                        break;
                    }
                } else {
                    x = nx;
                    y = ny;
                }
            }
        }

        cout << x << " " << y << " " << dir_name[dir];
        if (lost) {
            cout << " LOST";
        }
        cout << "\n";
    }

    return 0;
}
