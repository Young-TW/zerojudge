#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, R;
    while (cin >> N >> R) {
        bool returned[10005] = {false};
        for (int i = 0; i < R; ++i) {
            int id;
            cin >> id;
            returned[id] = true;
        }
        
        bool all_returned = true;
        for (int i = 1; i <= N; ++i) {
            if (!returned[i]) {
                cout << i << " ";
                all_returned = false;
            }
        }
        
        if (all_returned) {
            cout << "*";
        }
        cout << "\n";
    }
    
    return 0;
}
