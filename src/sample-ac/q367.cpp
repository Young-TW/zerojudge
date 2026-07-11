#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, r;
    while (cin >> N >> r) {
        int min_h = 51;
        for (int i = 0; i < N; ++i) {
            int a;
            cin >> a;
            if (a < min_h) {
                min_h = a;
            }
        }
        cout << min_h * r * r << "π\n";
    }
    
    return 0;
}
