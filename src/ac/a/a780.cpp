#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    double fo, fe, FA;
    while (cin >> fo >> fe >> FA) {
        if (fo == 0.0 && fe == 0.0 && FA == 0.0) {
            break;
        }
        double M = fo / fe;
        double FT = FA / M;
        cout << fixed << setprecision(2) << M << " " << FT << "\n";
    }
    
    return 0;
}
