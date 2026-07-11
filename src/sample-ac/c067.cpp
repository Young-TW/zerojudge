#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    int set_num = 1;
    while (cin >> n && n) {
        int h[55];
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            cin >> h[i];
            sum += h[i];
        }
        int avg = sum / n;
        int moves = 0;
        for (int i = 0; i < n; ++i) {
            if (h[i] > avg) {
                moves += h[i] - avg;
            }
        }
        cout << "Set #" << set_num << "\n";
        cout << "The minimum number of moves is " << moves << ".\n\n";
        set_num++;
    }
    
    return 0;
}
