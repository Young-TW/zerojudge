#include <iostream>
#include <string>
#include <set>

using namespace std;

set<string> final_boards;

bool checkWin(const string& board, char player) {
    for (int i = 0; i < 3; ++i) {
        if (board[i * 3] == player && board[i * 3 + 1] == player && board[i * 3 + 2] == player)
            return true;
        if (board[i] == player && board[i + 3] == player && board[i + 6] == player)
            return true;
    }
    if (board[0] == player && board[4] == player && board[8] == player)
        return true;
    if (board[2] == player && board[4] == player && board[6] == player)
        return true;
    return false;
}

void dfs(string& board, char current_player) {
    if (checkWin(board, 'O') || checkWin(board, 'X')) {
        final_boards.insert(board);
        return;
    }

    bool has_empty = false;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == '-') {
            has_empty = true;
            board[i] = current_player;
            dfs(board, current_player == 'O' ? 'X' : 'O');
            board[i] = '-';
        }
    }

    if (!has_empty) {
        final_boards.insert(board);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string board;
    while (cin >> board) {
        final_boards.clear();

        int count_O = 0, count_X = 0;
        for (char c : board) {
            if (c == 'O') count_O++;
            else if (c == 'X') count_X++;
        }

        char next_player;
        if (count_O > count_X) {
            next_player = 'X';
        } else if (count_X > count_O) {
            next_player = 'O';
        } else {
            next_player = 'O';
        }

        dfs(board, next_player);

        int total = final_boards.size();
        int win_O = 0, win_X = 0, draw = 0;

        for (const string& b : final_boards) {
            bool o_wins = checkWin(b, 'O');
            bool x_wins = checkWin(b, 'X');
            if (o_wins) win_O++;
            else if (x_wins) win_X++;
            else draw++;
        }

        cout << total << " " << win_O << " " << win_X << " " << draw << "\n";
    }
    return 0;
}
