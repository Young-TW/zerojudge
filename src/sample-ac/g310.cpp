#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<int> x(N);
        vector<int> y(N);
        for (int i = 0; i < N; ++i) {
            cin >> x[i];
        }
        for (int i = 0; i < N; ++i) {
            cin >> y[i];
        }
        
        int win = 0;
        int j = 0;
        for (int i = 0; i < N; ++i) {
            while (j < N && y[j] <= x[i]) {
                ++j;
            }
            if (j < N) {
                ++win;
                ++j;
            } else {
                break;
            }
        }
        cout << win << "\n";
    }
    return 0;
}
