#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <utility>
#include <sstream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> grid(15);
    while (cin >> grid[0]) {
        for (int i = 1; i < 15; ++i) {
            cin >> grid[i];
            if (grid[i].length() < 21) {
                grid[i].resize(21, 'o');
            }
        }
        
        string cmd_line;
        while (getline(cin, cmd_line) && cmd_line.empty()) {
            // 跳過空行，讀取指令行
        }
        
        int h = 15;
        int w = 21;
        
        int start_x = -1, start_y = -1;
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                if (grid[y][x] == 's') {
                    start_x = x;
                    start_y = y;
                    grid[y][x] = 'o';
                    break;
                }
            }
            if (start_x != -1) break;
        }
        
        if (start_x == -1) {
            start_x = 0;
            start_y = 0;
        }
        
        deque<pair<int, int>> snake;
        snake.push_back({start_x, start_y});
        
        vector<vector<bool>> is_snake(h, vector<bool>(w, false));
        is_snake[start_y][start_x] = true;
        
        istringstream iss(cmd_line);
        char dir;
        int steps;
        bool stopped = false;
        
        while (iss >> dir >> steps) {
            int dx = 0, dy = 0;
            if (dir == 'E') dx = 1;
            else if (dir == 'W') dx = -1;
            else if (dir == 'S') dy = 1;
            else if (dir == 'N') dy = -1;
            
            for (int i = 0; i < steps; ++i) {
                pair<int, int> head = snake.front();
                int nx = head.first + dx;
                int ny = head.second + dy;
                
                if (nx < 0 || nx >= w || ny < 0 || ny >= h) {
                    stopped = true;
                    break;
                }
                
                if (grid[ny][nx] == 'x') {
                    stopped = true;
                    break;
                }
                
                bool is_food = (grid[ny][nx] == '$');
                
                if (is_snake[ny][nx]) {
                    if (is_food || nx != snake.back().first || ny != snake.back().second) {
                        stopped = true;
                        break;
                    }
                }
                
                snake.push_front({nx, ny});
                is_snake[ny][nx] = true;
                
                if (is_food) {
                    grid[ny][nx] = 'o';
                } else {
                    pair<int, int> tail = snake.back();
                    snake.pop_back();
                    is_snake[tail.second][tail.first] = false;
                }
            }
            
            if (stopped) break;
        }
        
        for (size_t i = 0; i < snake.size(); ++i) {
            cout << snake[i].first << " " << snake[i].second << "\n";
        }
    }
    return 0;
}
