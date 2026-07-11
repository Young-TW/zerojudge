#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        for (int i = 0; i < N; ++i) {
            string plate;
            cin >> plate;
            
            int val1 = (plate[0] - 'A') * 676 + (plate[1] - 'A') * 26 + (plate[2] - 'A');
            int val2 = (plate[4] - '0') * 1000 + (plate[5] - '0') * 100 + (plate[6] - '0') * 10 + (plate[7] - '0');
            
            int diff = val1 - val2;
            if (diff < 0) {
                diff = -diff;
            }
            
            if (diff <= 100) {
                cout << "nice\n";
            } else {
                cout << "not nice\n";
            }
        }
    }
    
    return 0;
}
