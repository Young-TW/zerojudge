#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        long long poly[55] = {0};
        poly[0] = 1;
        for (int i = 0; i < N; ++i) {
            long long r;
            cin >> r;
            for (int j = i + 1; j >= 1; --j) {
                poly[j] = poly[j - 1] - r * poly[j];
            }
            poly[0] = -r * poly[0];
        }
        
        for (int i = N; i >= 0; --i) {
            long long c = poly[i];
            if (c == 0) {
                if (i == 0) {
                    cout << " + 0";
                }
                continue;
            }
            
            if (i == N) {
                if (i == 1) cout << "x";
                else cout << "x^" << i;
            } else {
                if (c > 0) cout << " + ";
                else {
                    cout << " - ";
                    c = -c;
                }
                
                if (i == 0) {
                    cout << c;
                } else {
                    if (c != 1) cout << c;
                    if (i == 1) cout << "x";
                    else cout << "x^" << i;
                }
            }
        }
        cout << " = 0\n";
    }
    return 0;
}
