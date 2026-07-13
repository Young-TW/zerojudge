#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int A[6], B[6];
    while (cin >> A[0] >> A[1] >> A[2] >> A[3] >> A[4] >> A[5]) {
        for (int i = 0; i < 6; ++i) {
            cin >> B[i];
        }
        int win = 0;
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                if (A[i] > B[j]) {
                    win++;
                }
            }
        }
        int total = 36;
        int g = gcd(win, total);
        cout << win / g << "/" << total / g << "\n";
    }
    return 0;
}
