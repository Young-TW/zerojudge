#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int apples[10];
    while (cin >> apples[0]) {
        for (int i = 1; i < 10; ++i) {
            cin >> apples[i];
        }
        int tao;
        cin >> tao;
        int max_h = tao + 30;
        int count = 0;
        for (int i = 0; i < 10; ++i) {
            if (apples[i] <= max_h) {
                count++;
            }
        }
        cout << count << "\n";
    }
    return 0;
}
