#include <iostream>
#include <string>
using namespace std;

int main() {
    int t;
    cin >> t;
    cin.ignore();
    for (int c = 1; c <= t; c++) {
        string team, judge;
        getline(cin, team);
        getline(cin, judge);
        string nospace;
        for (char ch : team) if (ch != ' ') nospace += ch;
        string verdict;
        if (team == judge) verdict = "Yes";
        else if (nospace == judge) verdict = "Output Format Error";
        else verdict = "Wrong Answer";
        cout << "Case " << c << ": " << verdict << "\n";
    }
    return 0;
}
