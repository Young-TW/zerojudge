#include <iostream>
#include <string>
#include <algorithm>
#include <initializer_list>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        for (int k = 0; k < N; ++k) {
            string s;
            cin >> s;
            int count[26] = {0};
            for (char c : s) {
                if (c >= 'A' && c <= 'Z') {
                    count[c - 'A']++;
                }
            }
            int m = count['M' - 'A'];
            int a = count['A' - 'A'] / 3;
            int r = count['R' - 'A'] / 2;
            int g = count['G' - 'A'];
            int i = count['I' - 'A'];
            int t = count['T' - 'A'];
            
            cout << min({m, a, r, g, i, t}) << "\n";
        }
    }
    
    return 0;
}
