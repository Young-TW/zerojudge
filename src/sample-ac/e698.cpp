#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int wo, ho, wre, hre;
    while (cin >> wo >> ho >> wre >> hre) {
        char cO, cRE;
        cin >> cO >> cRE;
        int n;
        cin >> n;
        
        int W = max(wo, wre);
        int padO = (W - wo) / 2;
        int padRE = (W - wre) / 2;

        string padO_str(padO, ' ');
        string padRE_str(padRE, ' ');
        string O_line = padO_str + string(wo, cO);
        string RE_line = padRE_str + string(wre, cRE);

        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            for (char c : s) {
                if (c == 'O') {
                    for (int j = 0; j < ho; ++j) {
                        cout << O_line << '\n';
                    }
                } else if (c == 'R') {
                    for (int j = 0; j < hre; ++j) {
                        cout << RE_line << '\n';
                    }
                }
            }
            cout << '\n';
        }
    }
    return 0;
}
