#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            int count[101] = {0};
            for (int i = 0; i < N; ++i) {
                int score;
                cin >> score;
                count[score]++;
            }
            int target = N / 2 + 1;
            int sum = 0;
            for (int i = 100; i >= 0; --i) {
                sum += count[i];
                if (sum >= target) {
                    cout << i << "\n";
                    break;
                }
            }
        }
    }
    return 0;
}
