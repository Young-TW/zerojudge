#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

int getShape(const string& s) {
    if (s == "Scissors") return 0;
    if (s == "Stone") return 1;
    if (s == "Paper") return 2;
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    int round = 0;
    int cnt1 = 0, cnt2 = 0, cnt3 = 0;
    
    while (getline(cin, line)) {
        string trimmed = trim(line);
        if (trimmed == "Game Over") {
            cout << "十六夜總計贏了" << cnt1 << "局比賽\n";
            cout << "紅美鈴總計贏了" << cnt2 << "局比賽\n";
            cout << "帕秋莉·諾雷姬總計贏了" << cnt3 << "局比賽\n";
        } else if (trimmed == "End") {
            if (cnt1 > cnt2 && cnt1 > cnt3) {
                cout << "趕上旅程\n";
            } else {
                cout << "繼續做家事\n";
            }
            break;
        } else if (!trimmed.empty()) {
            round++;
            stringstream ss(trimmed);
            string s1, s2, s3;
            getline(ss, s1, ',');
            getline(ss, s2, ',');
            getline(ss, s3, ',');
            
            s1 = trim(s1);
            s2 = trim(s2);
            s3 = trim(s3);
            
            int a = getShape(s1);
            int b = getShape(s2);
            int c = getShape(s3);
            
            if (a == -1) {
                cout << "十六夜贏了第" << round << "局的比賽\n";
                cnt1++;
            } else if (b == -1) {
                cout << "紅美鈴贏了第" << round << "局的比賽\n";
                cnt2++;
            } else if (c == -1) {
                cout << "帕秋莉·諾雷姬贏了第" << round << "局的比賽\n";
                cnt3++;
            } else {
                if (a == b && b == c) {
                    cout << "第" << round << "局不分勝負\n";
                } else if (a == b) {
                    if ((a - c + 3) % 3 == 1) {
                        cout << "帕秋莉·諾雷姬輸了第" << round << "局的比賽\n";
                        cnt1++;
                        cnt2++;
                    } else {
                        cout << "帕秋莉·諾雷姬贏了第" << round << "局的比賽\n";
                        cnt3++;
                    }
                } else if (b == c) {
                    if ((b - a + 3) % 3 == 1) {
                        cout << "十六夜輸了第" << round << "局的比賽\n";
                        cnt2++;
                        cnt3++;
                    } else {
                        cout << "十六夜贏了第" << round << "局的比賽\n";
                        cnt1++;
                    }
                } else if (a == c) {
                    if ((a - b + 3) % 3 == 1) {
                        cout << "紅美鈴輸了第" << round << "局的比賽\n";
                        cnt1++;
                        cnt3++;
                    } else {
                        cout << "紅美鈴贏了第" << round << "局的比賽\n";
                        cnt2++;
                    }
                } else {
                    cout << "第" << round << "局不分勝負\n";
                }
            }
        }
    }
    
    return 0;
}
