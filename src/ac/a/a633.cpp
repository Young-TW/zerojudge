#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 7‑segment order: a(top), b(upper‑left), c(upper‑right),
    // d(middle), e(lower‑left), f(lower‑right), g(bottom)
    const int segPos[3][3] = {
        { -1, 0, -1 },   // (0,1) -> a
        { 1, 3, 2 },     // (1,0)->b , (1,1)->d , (1,2)->c
        { 4, 6, 5 }      // (2,0)->e , (2,1)->g , (2,2)->f
    };
    
    // standard patterns for digits 0‑9 (3 strings each)
    const vector<array<string,3>> digitPic = {
        {" _ ",
         "| |",
         "|_|"}, //0
        {"   ",
         "  |",
         "  |"}, //1
        {" _ ",
         " _|",
         "|_ "}, //2
        {" _ ",
         " _|",
         " _|"}, //3
        {"   ",
         "|_|",
         "  |"}, //4
        {" _ ",
         "|_ ",
         " _|"}, //5
        {" _ ",
         "|_ ",
         "|_|"}, //6
        {" _ ",
         "  |",
         "  |"}, //7
        {" _ ",
         "|_|",
         "|_|"}, //8
        {" _ ",
         "|_|",
         " _|"}  //9
    };
    
    // compute mask for each digit
    int digitMask[10] = {0};
    for (int d = 0; d <= 9; ++d) {
        int mask = 0;
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                int seg = segPos[r][c];
                if (seg == -1) continue;
                char ch = digitPic[d][r][c];
                if ((seg == 0 || seg == 3 || seg == 6) && ch == '_')
                    mask |= (1 << seg);
                else if ((seg == 1 || seg == 2 || seg == 4 || seg == 5) && ch == '|')
                    mask |= (1 << seg);
            }
        }
        digitMask[d] = mask;
    }
    
    // modular inverses modulo 11 for 1..10
    int invMod[11] = {0};
    for (int i = 1; i < 11; ++i) {
        for (int j = 1; j < 11; ++j) {
            if ((i * j) % 11 == 1) { invMod[i] = j; break; }
        }
    }
    
    int T;
    if (!(cin >> T)) return 0;
    string dummy;
    getline(cin, dummy); // consume endline
    
    while (T--) {
        vector<string> rows(3);
        for (int i = 0; i < 3; ++i) getline(cin, rows[i]);
        // each row length should be 27, pad if shorter
        for (auto &s : rows) if ((int)s.size() < 27) s += string(27 - s.size(), ' ');
        
        int knownDigit[9];
        bool known[9];
        int unknownPos = -1;
        vector<int> unknownCandidates; // masks of possible digits for the unknown position
        int unknownMask = 0;
        bool multipleUnknown = false;
        int unknownCount = 0;
        // store masks for later use
        int observedMask[9];
        for (int pos = 0; pos < 9; ++pos) {
            int mask = 0;
            int col0 = pos * 3;
            for (int r = 0; r < 3; ++r) {
                for (int c = 0; c < 3; ++c) {
                    int seg = segPos[r][c];
                    if (seg == -1) continue;
                    char ch = rows[r][col0 + c];
                    if ((seg == 0 || seg == 3 || seg == 6) && ch == '_')
                        mask |= (1 << seg);
                    else if ((seg == 1 || seg == 2 || seg == 4 || seg == 5) && ch == '|')
                        mask |= (1 << seg);
                }
            }
            observedMask[pos] = mask;
            int exact = -1;
            for (int d = 0; d <= 9; ++d) if (mask == digitMask[d]) { exact = d; break; }
            if (exact != -1) {
                known[pos] = true;
                knownDigit[pos] = exact;
            } else {
                known[pos] = false;
                unknownCount++;
                unknownPos = pos;
                unknownMask = mask;
            }
        }
        
        // collect all possible solutions (as strings)
        set<string> solutions;
        
        // helper lambda to build number string from digit array
        auto buildNumber = [&](int digits[9]) -> string {
            string s;
            for (int i = 0; i < 9; ++i) s.push_back('0' + digits[i]);
            return s;
        };
        
        // case 1: no unknown positions
        if (unknownCount == 0) {
            long long sum = 0;
            for (int i = 0; i < 9; ++i) {
                int weight = 9 - i; // leftmost weight 9, rightmost weight 1
                sum += 1LL * weight * knownDigit[i];
            }
            if (sum % 11 == 0) {
                solutions.insert(buildNumber(knownDigit));
            }
        } else if (unknownCount == 1) {
            // compute candidates for the unknown position
            vector<int> candDigits;
            for (int d = 0; d <= 9; ++d) {
                int full = digitMask[d];
                // must be a proper superset (missing at least one segment)
                if ((observedMask[unknownPos] & ~full) == 0 && observedMask[unknownPos] != full) {
                    candDigits.push_back(d);
                }
            }
            // compute current weighted sum of known digits
            long long curSum = 0;
            for (int i = 0; i < 9; ++i) if (known[i]) {
                int w = 9 - i;
                curSum += 1LL * w * knownDigit[i];
            }
            int w = 9 - unknownPos; // weight of the missing digit
            int need = (int)((11 - (curSum % 11)) % 11);
            // solve w * x ≡ need (mod 11)
            int inv = invMod[w];
            int target = (int)((1LL * need * inv) % 11); // 0..10
            if (target <= 9) {
                // check if target is among candidates
                if (find(candDigits.begin(), candDigits.end(), target) != candDigits.end()) {
                    int digits[9];
                    for (int i = 0; i < 9; ++i) digits[i] = known[i] ? knownDigit[i] : 0;
                    digits[unknownPos] = target;
                    solutions.insert(buildNumber(digits));
                }
            }
        } else { // more than one unknown (should not happen per statement)
            // try each position as the single corrupted one
            for (int pos = 0; pos < 9; ++pos) if (!known[pos]) {
                // treat this pos as the only corrupted digit
                vector<int> candDigits;
                for (int d = 0; d <= 9; ++d) {
                    int full = digitMask[d];
                    if ((observedMask[pos] & ~full) == 0 && observedMask[pos] != full)
                        candDigits.push_back(d);
                }
                long long curSum = 0;
                for (int i = 0; i < 9; ++i) if (known[i]) {
                    int w = 9 - i;
                    curSum += 1LL * w * knownDigit[i];
                }
                int w = 9 - pos;
                int need = (int)((11 - (curSum % 11)) % 11);
                int inv = invMod[w];
                int target = (int)((1LL * need * inv) % 11);
                if (target <= 9 && find(candDigits.begin(), candDigits.end(), target) != candDigits.end()) {
                    int digits[9];
                    for (int i = 0; i < 9; ++i) digits[i] = known[i] ? knownDigit[i] : 0;
                    digits[pos] = target;
                    solutions.insert(buildNumber(digits));
                }
            }
        }
        
        if (solutions.empty())
            cout << "failure\n";
        else if (solutions.size() == 1)
            cout << *solutions.begin() << "\n";
        else
            cout << "ambiguous\n";
    }
    return 0;
}
