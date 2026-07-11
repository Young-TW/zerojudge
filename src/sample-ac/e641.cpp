#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int code[26] = {0};
    // A, E, I, O, U, H, W, Y are 0 by default
    code['B' - 'A'] = 1; code['F' - 'A'] = 1; code['P' - 'A'] = 1; code['V' - 'A'] = 1;
    code['C' - 'A'] = 2; code['G' - 'A'] = 2; code['J' - 'A'] = 2; code['K' - 'A'] = 2;
    code['Q' - 'A'] = 2; code['S' - 'A'] = 2; code['X' - 'A'] = 2; code['Z' - 'A'] = 2;
    code['D' - 'A'] = 3; code['T' - 'A'] = 3;
    code['L' - 'A'] = 4;
    code['M' - 'A'] = 5; code['N' - 'A'] = 5;
    code['R' - 'A'] = 6;
    
    string s;
    while (cin >> s) {
        int last_code = 0;
        for (char c : s) {
            if (c == 'H' || c == 'W') {
                continue;
            }
            int curr_code = code[c - 'A'];
            if (curr_code != 0) {
                if (curr_code != last_code) {
                    cout << curr_code;
                }
                last_code = curr_code;
            } else {
                last_code = 0;
            }
        }
        cout << "\n";
    }
    
    return 0;
}
