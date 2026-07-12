#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<bool> diff(n, false);
        bool is_jolly = true;
        
        int prev;
        cin >> prev;
        
        for (int i = 1; i < n; ++i) {
            int curr;
            cin >> curr;
            int d = curr - prev;
            if (d < 0) d = -d;
            if (d >= 1 && d < n) {
                diff[d] = true;
            } else {
                is_jolly = false;
            }
            prev = curr;
        }
        
        if (is_jolly) {
            for (int i = 1; i < n; ++i) {
                if (!diff[i]) {
                    is_jolly = false;
                    break;
                }
            }
        }
        
        if (is_jolly) {
            cout << "Jolly\n";
        } else {
            cout << "Not jolly\n";
        }
    }
    
    return 0;
}
