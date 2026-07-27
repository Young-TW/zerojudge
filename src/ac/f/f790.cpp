#include <bits/stdc++.h>
using namespace std;

string numToChinese(int n) {
    static const char* tbl[] = {
        "", "雙", "參", "肆", "伍", "陸", "柒", "捌", "玖", "拾"
    };
    if (n >= 2 && n <= 10) return tbl[n-1];
    return "";
}

// count patterns inside one line
void analyseLine(const string& s,
                 int& cntDeadFour,
                 int& cntLiveFour,
                 int& cntLiveThree) {
    int L = (int)s.size();

    // live three – contiguous (x o o o x)
    for (int i = 0; i + 4 < L; ++i) {
        if (s[i]=='x' && s[i+1]=='o' && s[i+2]=='o' && s[i+3]=='o' && s[i+4]=='x')
            ++cntLiveThree;
    }

    // live three – jump
    for (int i = 0; i + 5 < L; ++i) {
        // x o o x o x
        if (s[i]=='x' && s[i+1]=='o' && s[i+2]=='o' && s[i+3]=='x' && s[i+4]=='o' && s[i+5]=='x')
            ++cntLiveThree;
        // x o x o o x
        if (s[i]=='x' && s[i+1]=='o' && s[i+2]=='x' && s[i+3]=='o' && s[i+4]=='o' && s[i+5]=='x')
            ++cntLiveThree;
    }

    // runs of four stones
    for (int i = 0; i + 3 < L; ++i) {
        bool allO = true;
        for (int k = 0; k < 4; ++k)
            if (s[i+k] != 'o') { allO = false; break; }
        if (!allO) continue;

        // maximal run ?
        bool leftO  = (i-1 >= 0 && s[i-1] == 'o');
        bool rightO = (i+4 < L && s[i+4] == 'o');
        if (leftO || rightO) continue;          // part of longer line

        bool leftEmpty  = (i-1 >= 0 && s[i-1] == 'x');
        bool rightEmpty = (i+4 < L && s[i+4] == 'x');

        if (leftEmpty && rightEmpty) ++cntLiveFour;
        else if (leftEmpty ^ rightEmpty) ++cntDeadFour;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> board(7);
    while (cin >> board[0]) {
        for (int i = 1; i < 7; ++i) cin >> board[i];

        int cntDeadFour = 0, cntLiveFour = 0, cntLiveThree = 0;
        vector<string> lines;

        // rows
        for (int r = 0; r < 7; ++r) lines.push_back(board[r]);

        // columns
        for (int c = 0; c < 7; ++c) {
            string s;
            for (int r = 0; r < 7; ++r) s += board[r][c];
            lines.push_back(s);
        }

        // main diagonals (r - c = const)
        for (int d = -6; d <= 6; ++d) {
            string s;
            for (int r = 0; r < 7; ++r) {
                int c = r - d;
                if (0 <= c && c < 7) s += board[r][c];
            }
            if (s.size() >= 5) lines.push_back(s);
        }

        // anti diagonals (r + c = const)
        for (int sum = 0; sum <= 12; ++sum) {
            string s;
            for (int r = 0; r < 7; ++r) {
                int c = sum - r;
                if (0 <= c && c < 7) s += board[r][c];
            }
            if (s.size() >= 5) lines.push_back(s);
        }

        // analyse all lines
        for (const string& s : lines)
            analyseLine(s, cntDeadFour, cntLiveFour, cntLiveThree);

        // build output
        string out;
        if (cntDeadFour) {
            if (cntDeadFour > 1) out += numToChinese(cntDeadFour);
            out += "死四";
        }
        if (cntLiveFour) {
            if (cntLiveFour > 1) out += numToChinese(cntLiveFour);
            out += "活四";
        }
        if (cntLiveThree) {
            if (cntLiveThree > 1) out += numToChinese(cntLiveThree);
            out += "活三";
        }
        cout << out << '\n';
    }
    return 0;
}
