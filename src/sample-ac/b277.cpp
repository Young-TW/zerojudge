#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    long long T;

    while (cin >> n >> m >> T) {
        map<pair<int, int>, char> mirrors;
        for (int i = 0; i < n; ++i) {
            int x, y;
            char t;
            cin >> x >> y >> t;
            mirrors[{x, y}] = t;
        }

        int x = 0;
        int y = 0;
        // 方向：0: 右 (+x), 1: 上 (+y), 2: 左 (-x), 3: 下 (-y)
        int dir = 0; 

        long long steps = 0;

        while (steps < T) {
            int next_x = x;
            int next_y = y;

            if (dir == 0) next_x++;
            else if (dir == 1) next_y++;
            else if (dir == 2) next_x--;
            else if (dir == 3) next_y--;

            steps++;
            x = next_x;
            y = next_y;

            if (steps == T) break;

            if (mirrors.count({x, y})) {
                char type = mirrors[{x, y}];
                if (type == '/') {
                    if (dir == 0) dir = 1;       // 右 -> 上
                    else if (dir == 1) dir = 0;  // 上 -> 右
                    else if (dir == 2) dir = 3;  // 左 -> 下
                    else if (dir == 3) dir = 2;  // 下 -> 左
                } else if (type == '\\') {
                    if (dir == 0) dir = 3;       // 右 -> 下
                    else if (dir == 1) dir = 2;  // 上 -> 左
                    else if (dir == 2) dir = 1;  // 左 -> 上
                    else if (dir == 3) dir = 0;  // 下 -> 右
                }
            }
        }

        cout << x << " " << y << "\n";
    }

    return 0;
}
