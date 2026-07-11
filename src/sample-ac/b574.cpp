#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int K;
    while (cin >> K) {
        int current = 0;
        int max_people = 0;
        for (int i = 0; i < K; ++i) {
            int X, C;
            cin >> X >> C;
            if (C == 1) {
                current++;
            } else {
                current--;
            }
            if (current > max_people) {
                max_people = current;
            }
        }
        cout << max_people << "\n";
    }
    return 0;
}
