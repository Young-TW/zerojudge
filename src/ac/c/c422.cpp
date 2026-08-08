#include <bits/stdc++.h>
using namespace std;

/* ---------- helpers ---------- */

bool isRed(char ch) { return ch >= 'A' && ch <= 'Z'; }

bool isDiagonal(char ch) {               // 仕/士, 相/象, 傌/馬
    char lc = tolower(ch);
    return lc == 'a' || lc == 'e' || lc == 'h';
}

/* file number from column, according to the player's view */
int fileFromCol(int col, bool red) {      // col 0..8
    return red ? 9 - col : col + 1;
}

/* Chinese numerals 1..9 */
const string CN[10] = {"", "一","二","三","四","五","六","七","八","九"};
string cn(int n) { return CN[n]; }
string ar(int n) { return to_string(n); }

/* piece name */
string pieceName(char ch) {
    switch (ch) {
        case 'K': return "帥";
        case 'A': return "仕";
        case 'E': return "相";
        case 'R': return "俥";
        case 'H': return "傌";
        case 'C': return "炮";
        case 'P': return "兵";
        case 'k': return "將";
        case 'a': return "士";
        case 'e': return "象";
        case 'r': return "車";
        case 'h': return "馬";
        case 'c': return "砲";
        case 'p': return "卒";
        default:  return "";
    }
}

/* ---------- build notation for one move ---------- */
string makeNotation(const vector<string>& prev,
                    const vector<string>& cur) {
    int sr=-1, sc=-1, dr=-1, dc=-1;
    for (int r=0;r<10;++r){
        for (int c=0;c<9;++c){
            if (prev[r][c]!=cur[r][c]){
                if (prev[r][c]!='.' && cur[r][c]=='.'){
                    sr=r; sc=c;
                }else{
                    dr=r; dc=c;
                }
            }
        }
    }

    char piece = cur[dr][dc];
    bool red = isRed(piece);
    string name = pieceName(piece);

    int srcFile = fileFromCol(sc, red);
    int dstFile = fileFromCol(dc, red);

    bool forward = (red && dr < sr) || (!red && dr > sr);

    string dir, fourth;

    if (isDiagonal(piece)) {                     // 仕/士, 相/象, 傌/馬
        dir = forward ? "進" : "退";
        fourth = red ? cn(dstFile) : ar(dstFile);
    } else {                                     // straight pieces
        if (sc == dc) {                          // vertical
            dir = forward ? "進" : "退";
            int dist = abs(sr - dr);
            fourth = red ? cn(dist) : ar(dist);
        } else {                                 // horizontal
            dir = "平";
            fourth = red ? cn(dstFile) : ar(dstFile);
        }
    }

    /* ----- special 前/後 case -----
       適用於除了 仕/士(a) 與 相/象(e) 以外的所有兵種，
       包含 傌/馬(h)（斜向移動但仍可能同路需分前後）。 */
    char lcPiece = tolower(piece);
    if (lcPiece != 'a' && lcPiece != 'e') {
        int cnt = 0;
        int otherR = -1, otherC = -1;
        for (int r=0;r<10;++r){
            for (int c=0;c<9;++c){
                if (prev[r][c]==piece && fileFromCol(c, red)==srcFile){
                    ++cnt;
                    if (!(r==sr && c==sc)){
                        otherR=r; otherC=c;
                    }
                }
            }
        }
        if (cnt==2) {
            bool srcIsFront = red ? (sr < otherR) : (sr > otherR);
            string prefix = srcIsFront ? "前" : "後";
            return prefix + name + dir + fourth;
        }
    }

    // normal notation
    string second = red ? cn(srcFile) : ar(srcFile);
    return name + second + dir + fourth;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<string>> boards;
    vector<string> cur;
    string line;
    while (getline(cin, line)) {
        if (line == "#") {
            if (!cur.empty()) {
                boards.push_back(cur);
                cur.clear();
            }
        } else {
            cur.push_back(line);
        }
    }
    if (!cur.empty()) boards.push_back(cur);   // safety

    vector<string> redMoves, blackMoves;
    for (size_t i = 0; i + 1 < boards.size(); ++i) {
        string notation = makeNotation(boards[i], boards[i+1]);
        if (i % 2 == 0) redMoves.push_back(notation);
        else            blackMoves.push_back(notation);
    }

    int lines = static_cast<int>(boards.size() / 2);
    for (int i = 0; i < lines; ++i) {
        cout << setw(3) << setfill('0') << (i + 1) << ". ";
        cout << redMoves[i];
        if (i < (int)blackMoves.size()) cout << ' ' << blackMoves[i];
        cout << '\n';
    }
    return 0;
}
