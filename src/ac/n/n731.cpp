#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int run = 1;
    while (true) {
        int n;
        if (!(cin >> n)) return 0;          // EOF
        if (n == 0) break;                  // termination
        
        string dummy;
        getline(cin, dummy);                // consume end‑of‑line after the number
        
        vector<string> refLines(n);
        string refAll, refDigits;
        for (int i = 0; i < n; ++i) {
            getline(cin, refLines[i]);
            if (i) refAll.push_back('\n');
            refAll += refLines[i];
            for (char ch : refLines[i])
                if (isdigit(static_cast<unsigned char>(ch)))
                    refDigits.push_back(ch);
        }
        
        int m;
        cin >> m;
        getline(cin, dummy);                // consume end‑of‑line
        vector<string> teamLines(m);
        string teamAll, teamDigits;
        for (int i = 0; i < m; ++i) {
            getline(cin, teamLines[i]);
            if (i) teamAll.push_back('\n');
            teamAll += teamLines[i];
            for (char ch : teamLines[i])
                if (isdigit(static_cast<unsigned char>(ch)))
                    teamDigits.push_back(ch);
        }
        
        string verdict;
        if (refAll == teamAll) {
            verdict = "Accepted";
        } else if (refDigits == teamDigits) {
            verdict = "Presentation Error";
        } else {
            verdict = "Wrong Answer";
        }
        
        cout << "Run #" << run << ": " << verdict << "\n";
        ++run;
    }
    return 0;
}
