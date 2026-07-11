#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int doomsdays[13] = {0, 10, 21, 7, 4, 9, 6, 11, 8, 5, 10, 7, 12};
    const char* days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    
    int T;
    while (cin >> T) {
        while (T--) {
            int M, D;
            cin >> M >> D;
            int diff = D - doomsdays[M];
            diff = ((diff % 7) + 7) % 7;
            cout << days[diff] << "\n";
        }
    }
    
    return 0;
}
