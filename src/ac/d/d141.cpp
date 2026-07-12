#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    if (cin >> N) {
        while (N--) {
            long long x1, y1, x2, y2, x3, y3;
            char c;
            cin >> x1 >> c >> y1 >> x2 >> c >> y2 >> x3 >> c >> y3;
            
            if ((x2 - x1) * (y3 - y1) == (x3 - x1) * (y2 - y1)) {
                cout << "collinear\n";
            } else {
                cout << "not collinear\n";
            }
        }
    }
    
    return 0;
}
