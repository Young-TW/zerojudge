#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int C;
    if (cin >> C) {
        while (C--) {
            int N;
            cin >> N;
            int scores[1000];
            int sum = 0;
            for (int i = 0; i < N; ++i) {
                cin >> scores[i];
                sum += scores[i];
            }
            double avg = static_cast<double>(sum) / N;
            int count = 0;
            for (int i = 0; i < N; ++i) {
                if (scores[i] > avg) {
                    ++count;
                }
            }
            double percentage = static_cast<double>(count) / N * 100.0;
            cout << fixed << setprecision(3) << percentage << "%\n";
        }
    }
    
    return 0;
}
