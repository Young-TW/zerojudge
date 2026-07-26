#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_map<string, char> code2ch;
    // initialise the table (order exactly as in the statement)
    code2ch["123457"] = 'A';
    code2ch["1234567"] = 'B';
    code2ch["456"] = 'C';
    code2ch["1580"] = 'D';
    code2ch["12456"] = 'E';
    code2ch["1249"] = 'F';
    code2ch["12569"] = 'G';
    code2ch["13457"] = 'H';
    code2ch["37"] = 'I';
    code2ch["3567"] = 'J';
    code2ch["13459"] = 'K';
    code2ch["156"] = 'L';
    code2ch["12357"] = 'M';
    code2ch["3579"] = 'N';
    code2ch["123567"] = 'O';
    code2ch["1458"] = 'P';
    code2ch["12347"] = 'Q';
    code2ch["123459"] = 'R';
    code2ch["12467"] = 'S';
    code2ch["278"] = 'T';
    code2ch["13567"] = 'U';
    code2ch["1379"] = 'V';
    code2ch["135790"] = 'W';
    code2ch["90"] = 'X';
    code2ch["1347"] = 'Y';
    code2ch["23456"] = 'Z';

    const int maxLen = 7;               // length of the longest code (B)

    string line;
    while (getline(cin, line)) {
        string out;
        string digitBuf;

        auto decode = [&](const string &blk) -> string {
            string res;
            size_t pos = 0;
            while (pos < blk.size()) {
                bool matched = false;
                // try longest possible prefix
                for (int len = maxLen; len >= 1; --len) {
                    if (pos + len > blk.size()) continue;
                    string sub = blk.substr(pos, len);
                    auto it = code2ch.find(sub);
                    if (it != code2ch.end()) {
                        res.push_back(it->second);
                        pos += len;
                        matched = true;
                        break;
                    }
                }
                if (!matched) { // must be a single '0' → blank
                    res.push_back(' ');
                    ++pos; // consume the '0'
                }
            }
            return res;
        };

        for (char c : line) {
            if (c >= '0' && c <= '9') {
                digitBuf.push_back(c);
            } else {
                if (!digitBuf.empty()) {
                    out += decode(digitBuf);
                    digitBuf.clear();
                }
                out.push_back(c); // original letter or space
            }
        }
        if (!digitBuf.empty()) {
            out += decode(digitBuf);
        }

        cout << out << '\n';
    }
    return 0;
}
