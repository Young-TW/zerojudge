#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <array>

using namespace std;

struct State {
    array<unsigned char, 25> board;
    int g;
    int f;
    int blank_pos;

    bool operator>(const State& other) const {
        return f > other.f;
    }
};

const int target[25] = {
    0, 1, 2, 3, 4,
    5, 6, 7, 8, 9,
    10, 11, 12, 13, 14,
    15, 16, 17, 18, 19,
    20, 21, 22, 23, 24
};

const int target_pos[25] = {
    0, 1, 2, 3, 4,
    5, 6, 7, 8, 9,
    10, 11, 12, 13, 14,
    15, 16, 17, 18, 19,
    20, 21, 22, 23, 24
};

const int target_row[25] = {
    0, 0, 0, 0, 0,
    1, 1, 1, 1, 1,
    2, 2, 2, 2, 2,
    3, 3, 3, 3, 3,
    4, 4, 4, 4, 4
};

const int target_col[25] = {
    0, 1, 2, 3, 4,
    0, 1, 2, 3, 4,
    0, 1, 2, 3, 4,
    0, 1, 2, 3, 4,
    0, 1, 2, 3, 4
};

int row_diff[25][25];
int col_diff[25][25];

void precompute_diff() {
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 25; ++j) {
            row_diff[i][j] = abs(target_row[i] - target_row[j]);
            col_diff[i][j] = abs(target_col[i] - target_col[j]);
        }
    }
}

int heuristic(const array<unsigned char, 25>& board) {
    int dist = 0;
    for (int i = 0; i < 25; ++i) {
        int val = board[i];
        if (val != 0) {
            dist += row_diff[val][i] + col_diff[val][i];
        }
    }
    return dist;
}

int solve(array<unsigned char, 25>& start_board) {
    int inversions = 0;
    for (int i = 0; i < 25; ++i) {
        if (start_board[i] == 0) continue;
        for (int j = i + 1; j < 25; ++j) {
            if (start_board[j] == 0) continue;
            if (start_board[i] > start_board[j]) {
                inversions++;
            }
        }
    }
    if (inversions % 2 != 0) {
        return -1;
    }

    int start_blank = -1;
    for (int i = 0; i < 25; ++i) {
        if (start_board[i] == 0) {
            start_blank = i;
            break;
        }
    }

    priority_queue<State, vector<State>, greater<State>> pq;
    unordered_map<long long, int> dist;

    int start_h = heuristic(start_board);
    State start_state = {start_board, 0, start_h, start_blank};
    pq.push(start_state);
    dist[*(long long*)(start_board.data()) ^ (*(long long*)(start_board.data() + 8) << 7)] = 0;

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        long long curr_hash = *(long long*)curr.board.data() ^ (*(long long*)(curr.board.data() + 8) << 7);
        if (dist.count(curr_hash) && dist[curr_hash] < curr.g) {
            continue;
        }

        if (curr.blank_pos == 0) {
            bool solved = true;
            for (int i = 0; i < 25; ++i) {
                if (curr.board[i] != target[i]) {
                    solved = false;
                    break;
                }
            }
            if (solved) {
                return curr.g;
            }
        }

        int r = curr.blank_pos / 5;
        int c = curr.blank_pos % 5;

        const int dr[] = {-1, 1, 0, 0};
        const int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < 5 && nc >= 0 && nc < 5) {
                int next_blank = nr * 5 + nc;
                State next = curr;
                
                int moved_val = next.board[next_blank];
                next.board[curr.blank_pos] = moved_val;
                next.board[next_blank] = 0;
                
                next.g = curr.g + 1;
                
                int h_delta = 0;
                h_delta -= row_diff[moved_val][next_blank] + col_diff[moved_val][next_blank];
                h_delta += row_diff[moved_val][curr.blank_pos] + col_diff[moved_val][curr.blank_pos];
                
                next.f = next.g + curr.f - curr.g + h_delta;
                next.blank_pos = next_blank;

                long long next_hash = *(long long*)next.board.data() ^ (*(long long*)(next.board.data() + 8) << 7);
                if (!dist.count(next_hash) || dist[next_hash] > next.g) {
                    dist[next_hash] = next.g;
                    pq.push(next);
                }
            }
        }
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute_diff();

    int T;
    while (cin >> T) {
        while (T--) {
            array<unsigned char, 25> board;
            for (int i = 0; i < 25; ++i) {
                int val;
                cin >> val;
                board[i] = val;
            }

            int ans = solve(board);
            if (ans == -1) {
                cout << "I must cheat!!!\n";
            } else {
                cout << ans << "\n";
            }
        }
    }

    return 0;
}
