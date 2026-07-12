#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

bool hasNonASCII(const string& s) {
    for (size_t i = 0; i < s.size(); i++) {
        if ((unsigned char)s[i] > 127) return true;
    }
    return false;
}

string trimStr(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

int computeHCP(const string& cards) {
    int hcp = 0;
    istringstream iss(cards);
    string card;
    while (iss >> card) {
        if (card[0] == 'A') hcp += 4;
        else if (card[0] == 'K') hcp += 3;
        else if (card[0] == 'Q') hcp += 2;
        else if (card[0] == 'J') hcp += 1;
    }
    return hcp;
}

int countSuit(const string& cards, char suit) {
    int cnt = 0;
    istringstream iss(cards);
    string card;
    while (iss >> card) {
        if (card.size() >= 2 && card[1] == suit) cnt++;
    }
    return cnt;
}

string getBid(const string& cards) {
    int hcp = computeHCP(cards);
    int s = countSuit(cards, 'S');
    int h = countSuit(cards, 'H');
    int d = countSuit(cards, 'D');
    int c = countSuit(cards, 'C');

    vector<int> suits = {s, h, d, c};
    sort(suits.begin(), suits.end());
    bool balanced = (suits[0]==3 && suits[1]==3 && suits[2]==3 && suits[3]==4) ||
                    (suits[0]==2 && suits[1]==3 && suits[2]==4 && suits[3]==4);

    if (hcp >= 20) return "2C";
    if (hcp >= 15 && hcp <= 18 && balanced) return "1NT";
    if (hcp >= 12 && s >= 5) return "1S";
    if (hcp >= 12 && h >= 5) return "1H";
    if (hcp >= 12 && d >= 3) return "1D";
    if (hcp >= 12) return "1C";
    return "Pass";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    vector<string> cardLines;

    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();

        string trimmed = trimStr(line);

        if (trimmed.empty()) {
            cout << "\n";
            continue;
        }

        if (hasNonASCII(line)) {
            cout << trimmed << "\n";
            continue;
        }

        if (trimmed.size() == 1 && (trimmed[0]=='N' || trimmed[0]=='E' || trimmed[0]=='S' || trimmed[0]=='W')) {
            int dirIdx;
            if (trimmed[0]=='N') dirIdx=0;
            else if (trimmed[0]=='E') dirIdx=1;
            else if (trimmed[0]=='S') dirIdx=2;
            else dirIdx=3;

            string result = "All Pass";
            for (int i = 0; i < 4; i++) {
                int idx = (dirIdx + i) % 4;
                string bid = getBid(cardLines[idx]);
                if (bid != "Pass") {
                    result = bid;
                    break;
                }
            }
            cout << result << "\n";
            cardLines.clear();
            continue;
        }

        cardLines.push_back(trimmed);
    }

    return 0;
}
