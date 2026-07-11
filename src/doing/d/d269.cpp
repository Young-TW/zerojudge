#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            vector<double> S(N);
            for (int i = 0; i < N; ++i) {
                cin >> S[i];
            }
            
            sort(S.begin(), S.end(), greater<double>());
            
            double max_area = 0.0;
            for (int i = 0; i + 2 < N; ++i) {
                if (S[i] < S[i+1] + S[i+2]) {
                    double a = S[i];
                    double b = S[i+1];
                    double c = S[i+2];
                    double s = (a + b + c) / 2.0;
                    max_area = sqrt(s * (s - a) * (s - b) * (s - c));
                    break;
                }
            }
            
            cout << fixed << setprecision(2) << max_area << "\n";
        }
    }
    
    return 0;
}
