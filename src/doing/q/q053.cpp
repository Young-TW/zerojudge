#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    cin.ignore(10000, '\n');

    int rows = n + 2;
    int cols = m + 2;
    vector<int> maze(rows * cols, -1);

    for (int i = 1; i <= n; ++i) {
        string line;
        getline(cin, line);
        for (int j = 1; j <= m; ++j) {
            if (j - 1 < line.length() && line[j - 1] == ' ') {
                maze[i * cols + j] = 0;
            }
        }
    }

    int start = 2 * cols + 2;
    int end = (n - 1) * cols + (m - 1);

    if (maze[start] == -1 || maze[end] == -1) {
        cout << 0 << "\n";
        return 0;
    }

    maze[start] = 1;
    vector<int> q;
    q.reserve(rows * cols);
    q.push_back(start);
    int head = 0;

    while (head < q.size()) {
        int curr = q[head++];

        if (curr == end) {
            cout << maze[curr] - 1 << "\n";
            return 0;
        }

        int dist = maze[curr];

        if (maze[curr + 1] == 0) {
            maze[curr + 1] = dist + 1;
            q.push_back(curr + 1);
        }
        if (maze[curr - 1] == 0) {
            maze[curr - 1] = dist + 1;
            q.push_back(curr - 1);
        }
        if (maze[curr + cols] == 0) {
            maze[curr + cols] = dist + 1;
            q.push_back(curr + cols);
        }
        if (maze[curr - cols] == 0) {
            maze[curr - cols] = dist + 1;
            q.push_back(curr - cols);
        }
    }

    cout << 0 << "\n";
    return 0;
}
