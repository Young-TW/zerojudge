#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        for (int i = 1; i <= T; ++i) {
            int d1, m1, y1, d2, m2, y2;
            char slash;
            cin >> d1 >> slash >> m1 >> slash >> y1;
            cin >> d2 >> slash >> m2 >> slash >> y2;
            
            int age = y1 - y2;
            if (m1 < m2 || (m1 == m2 && d1 < d2)) {
                age--;
            }
            
            cout << "Case #" << i << ": ";
            if (age < 0) {
                cout << "Invalid birth date\n";
            } else if (age > 130) {
                cout << "Check birth date\n";
            } else {
                cout << age << "\n";
            }
        }
    }
    return 0;
}
