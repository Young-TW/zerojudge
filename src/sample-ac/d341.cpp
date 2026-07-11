#include <iostream>
#include <string>
#include <vector>

using namespace std;

int strToIdx(const string& s) {
    if (s[0] >= '1' && s[0] <= '9') {
        int num = s[0] - '1';
        if (s[1] == 'T') return num;
        if (s[1] == 'S') return 9 + num;
        if (s[1] == 'W') return 18 + num;
    }
    if (s == "DONG") return 27;
    if (s == "NAN") return 28;
    if (s == "XI") return 29;
    if (s == "BEI") return 30;
    if (s == "ZHONG") return 31;
    if (s == "FA") return 32;
    if (s == "BAI") return 33;
    return -1;
}

string idxToStr(int idx) {
    if (idx < 9) return string(1, '1' + idx) + "T";
    if (idx < 18) return string(1, '1' + idx - 9) + "S";
    if (idx < 27) return string(1, '1' + idx - 18) + "W";
    if (idx == 27) return "DONG";
    if (idx == 28) return "NAN";
    if (idx == 29) return "XI";
    if (idx == 30) return "BEI";
    if (idx == 31) return "ZHONG";
    if (idx == 32) return "FA";
    if (idx == 33) return "BAI";
    return "";
}

bool check(int hand[]) {
    for (int i = 0; i < 34; ++i) {
        if (hand[i] > 0) {
            if (hand[i] >= 3) {
                hand[i] -= 3;
                if (check(hand)) {
                    hand[i] += 3;
                    return true;
                }
                hand[i] += 3;
            }
            if (i < 27 && i % 9 <= 6 && hand[i+1] >= 1 && hand[i+2] >= 1) {
                hand[i]--;
                hand[i+1]--;
                hand[i+2]--;
                if (check(hand)) {
                    hand[i]++;
                    hand[i+1]++;
                    hand[i+2]++;
                    return true;
                }
                hand[i]++;
                hand[i+1]++;
                hand[i+2]++;
            }
            return false;
        }
    }
    return true;
}

bool isWinningHand(int hand[]) {
    for (int i = 0; i < 34; ++i) {
        if (hand[i] >= 2) {
            hand[i] -= 2;
            if (check(hand)) {
                hand[i] += 2;
                return true;
            }
            hand[i] += 2;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    int caseNum = 1;
    while (cin >> s && s != "0") {
        int hand[34] = {0};
        hand[strToIdx(s)]++;
        for (int i = 0; i < 12; ++i) {
            cin >> s;
            hand[strToIdx(s)]++;
        }
        
        vector<int> ready;
        for (int i = 0; i < 34; ++i) {
            if (hand[i] < 4) {
                hand[i]++;
                if (isWinningHand(hand)) {
                    ready.push_back(i);
                }
                hand[i]--;
            }
        }
        
        cout << "Case " << caseNum << ":";
        if (ready.empty()) {
            cout << " Not ready";
        } else {
            for (size_t i = 0; i < ready.size(); ++i) {
                cout << " " << idxToStr(ready[i]);
            }
        }
        cout << "\n";
        caseNum++;
    }
    return 0;
}
