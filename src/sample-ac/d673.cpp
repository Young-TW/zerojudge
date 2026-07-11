#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int S;
    int case_num = 1;
    while (cin >> S && S >= 0) {
        int produced[12];
        int required[12];
        for (int i = 0; i < 12; ++i) {
            cin >> produced[i];
        }
        for (int i = 0; i < 12; ++i) {
            cin >> required[i];
        }
        
        cout << "Case " << case_num++ << ":\n";
        int stock = S;
        for (int i = 0; i < 12; ++i) {
            if (stock >= required[i]) {
                stock -= required[i];
                cout << "No problem! :D\n";
            } else {
                cout << "No problem. :(\n";
            }
            stock += produced[i];
        }
    }
    
    return 0;
}
